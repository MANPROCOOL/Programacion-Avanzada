#ifndef JUGADOROPTIMO_H
#define JUGADOROPTIMO_H

#include "Actuacion.h"
#include "Jugador.h"
#include "Marcador.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class JugadorOptimo : public Jugador {
private:
  // 10 logical categories: 0..5 = balas..senas, 6 = escalera, 7 = full,
  // 8 = poker, 9 = grande (with count 0, 1, or 2).
  // Base states: 2^9 * 3 = 1536.
  // Full states include 3-bit respeta-used mask (escalera=1, full=2, poker=4):
  // 1536 * 8 = 12288 slots (5184 valid reachable states).
  static constexpr int NUM_HANDS = 252;
  static constexpr int NUM_KEEPS = 210;
  static constexpr int NUM_BASE_STATES = 1536;
  static constexpr int NUM_STATES = 12288;
  static constexpr int NUM_CATS = 10;

  struct Transition {
    uint8_t handId;
    double prob;
  };

  struct KeepOption {
    uint8_t keepId;
    uint8_t rerollCount;
  };

  struct ManoHandInfo {
    uint8_t handId;
    uint8_t respBit; // 1 = escalera, 2 = full, 4 = poker
    double prob;
  };

  struct DPModel {
    std::array<std::array<int, 5>, NUM_HANDS> hands{};
    uint8_t handLookup[6][6][6][6][6]{};
    uint8_t keepLookup[5][5][5][5][5][5]{};
    std::array<std::vector<Transition>, NUM_KEEPS> transitions;
    std::array<std::vector<KeepOption>, NUM_HANDS> handKeepOpts;
    std::vector<ManoHandInfo> manoHands;

    // Per-hand scoring & borres tables
    int8_t vuelquePts[NUM_HANDS][NUM_CATS]{};
    int8_t manoPts[NUM_HANDS][NUM_CATS]{};
    bool isDormida[NUM_HANDS]{};
    std::array<std::vector<uint16_t>, NUM_HANDS> flipUsefulMasks;

    // Precomputed optimal DP tables
    std::vector<double> V;
    std::vector<double> W2_yaAn;

    // sobreVal[stateId][cat][scoreIdx] stores W2_sobre(stateId, p + V[next(stateId, cat)])
    std::vector<std::array<std::array<double, 6>, NUM_CATS>> sobreVal;

    // Per-base-state base Q2 scores & per-state precomputed keepEV tables for O(1) runtime
    std::vector<std::array<double, NUM_HANDS>> bestVuelque;
    std::vector<std::array<double, NUM_HANDS>> bestFullReroll;
    std::vector<std::array<double, NUM_KEEPS>> keepEV1Table;
    std::vector<std::array<double, NUM_KEEPS>> keepEV2YaAnTable;

    DPModel() {
      buildHandsAndKeeps();
      buildTransitions();
      buildScoringTables();
      solveDP();
    }

    static bool esEscaleraMano(std::array<int, 5> d) {
      std::sort(d.begin(), d.end());
      int i = (d[0] == 1 && d[1] == 3) ? 1 : 0;
      for (; i < 4; ++i) {
        if (d[i + 1] != d[i] + 1) return false;
      }
      return true;
    }

    static bool esFullMano(std::array<int, 5> d) {
      std::sort(d.begin(), d.end());
      return (d[0] == d[1] && d[3] == d[4] && d[0] != d[4]) &&
             (d[2] == d[3] || d[2] == d[1]);
    }

    static bool esPokerMano(std::array<int, 5> d) {
      std::sort(d.begin(), d.end());
      return ((d[0] == d[3]) && (d[3] != d[4])) ||
             ((d[1] == d[4]) && (d[0] != d[1]));
    }

    static bool esDormidaHand(const std::array<int, 5> &d) {
      for (int i = 1; i < 5; ++i) {
        if (d[i] != d[0]) return false;
      }
      return true;
    }

    static int sumaChica(int valor, const std::array<int, 5> &dList) {
      std::array<int, 5> d = dList;
      std::sort(d.begin(), d.end());
      if (d[0] == valor && d[4] == valor) return 4 * valor;
      int s = 0, vCount = 0;
      for (int v : dList) {
        if (v == valor) {
          s += valor;
        } else if (v == 7 - valor && vCount < 2) {
          s += valor;
          vCount++;
        }
      }
      return s;
    }

    static int sumaChicaSinVuelque(int valor, const std::array<int, 5> &dList) {
      int s = 0;
      for (int v : dList) {
        if (v == valor) s += valor;
      }
      return s;
    }

    static bool esEscaleraHuevo(const std::array<int, 5> &dList) {
      int c[7] = {};
      for (int v : dList) c[v]++;
      if (c[3] + c[4] != 2) return false;
      int s = c[1] + c[6];
      if (s == 0 || s == 3) return false;
      if (c[3] == 0 || c[4] == 0) {
        if ((c[1] == 2 || c[6] == 2) && c[2] == 1) return false;
      }
      return true;
    }

    static bool esFullHuevo(const std::array<int, 5> &dList) {
      int c[7] = {};
      for (int v : dList) c[v]++;
      for (int i = 1; i <= 2; ++i) {
        int s = c[i] + c[7 - i];
        if (s == 0) continue;
        if (s == 5) return true;
        if (s == 1 || s == 4) return false;
        int s2 = c[i + 1] + c[7 - i - 1];
        if (s2 == 1 || s + s2 == 4) return false;
      }
      return true;
    }

    static bool esPokerHuevo(const std::array<int, 5> &dList) {
      int c[7] = {};
      for (int v : dList) c[v]++;
      for (int i = 1; i <= 3; ++i) {
        if (c[i] + c[7 - i] >= 4) return true;
      }
      return false;
    }

    static bool esGrande(std::array<int, 5> d) {
      std::sort(d.begin(), d.end());
      if (d[0] == 7 - d[4]) {
        if (d[0] == d[3] || d[1] == d[4]) return true;
        if ((d[0] == d[2] && d[3] == d[4]) || (d[2] == d[4] && d[0] == d[1])) {
          return true;
        }
      }
      return false;
    }

    static uint16_t usefulMaskOfHand(const std::array<int, 5> &d) {
      uint16_t mask = 0;
      for (int k = 1; k <= 6; ++k) {
        if (sumaChicaSinVuelque(k, d) > 0) mask |= (1u << (k - 1));
      }
      if (esEscaleraMano(d)) mask |= (1u << 6);
      if (esFullMano(d)) mask |= (1u << 7);
      if (esPokerMano(d)) mask |= (1u << 8);
      if (esDormidaHand(d)) mask |= (1u << 9);
      return mask;
    }

    uint8_t getHandId(std::array<int, 5> d) const {
      std::sort(d.begin(), d.end());
      return handLookup[d[0] - 1][d[1] - 1][d[2] - 1][d[3] - 1][d[4] - 1];
    }

    uint8_t getKeepIdFromCounts(const int c[6]) const {
      return keepLookup[c[0]][c[1]][c[2]][c[3]][c[4]][c[5]];
    }

    static int baseNextState(int baseState, int cat) {
      int mask9 = baseState / 3;
      int gCount = baseState % 3;
      if (cat < 9) {
        return (mask9 & ~(1 << cat)) * 3 + gCount;
      }
      return mask9 * 3 + (gCount - 1);
    }

    static int nextState(int stateId, int cat) {
      int baseState = stateId >> 3;
      int rMask = stateId & 7;
      return (baseNextState(baseState, cat) << 3) | rMask;
    }

    static uint16_t openMask10(int baseState) {
      int mask9 = baseState / 3;
      int gCount = baseState % 3;
      return static_cast<uint16_t>(mask9 | (gCount > 0 ? (1 << 9) : 0));
    }

    // Returns 3-bit mask of respetas available in (baseState, rMask):
    // bit 0 = escalera closed & not yet respected, bit 1 = full, bit 2 = poker.
    static int availRespMask(int baseState, int rMask) {
      int mask9 = baseState / 3;
      int closedMayores = ((~mask9) >> 6) & 7;
      return closedMayores & (~rMask & 7);
    }

    static bool isValidState(int baseState, int rMask) {
      int mask9 = baseState / 3;
      int openMayores = (mask9 >> 6) & 7;
      return (openMayores & rMask) == 0;
    }

    bool inclBorres(uint16_t m10, int handId) const {
      for (uint16_t um : flipUsefulMasks[handId]) {
        if ((m10 & um) == 0) return true;
      }
      return false;
    }

    static int scoreToIdx(int cat, int pts) {
      if (cat < 6) {
        int v = cat + 1;
        return pts / v; // 0..5
      }
      if (cat == 6) return pts == 25 ? 2 : (pts == 20 ? 1 : 0);
      if (cat == 7) return pts == 35 ? 2 : (pts == 30 ? 1 : 0);
      if (cat == 8) return pts == 45 ? 2 : (pts == 40 ? 1 : 0);
      return pts == 50 ? 1 : 0;
    }

    static int numScoreVals(int cat) {
      if (cat < 6) return 6;
      if (cat < 9) return 3;
      return 2;
    }

    static int idxToScore(int cat, int idx) {
      if (cat < 6) return idx * (cat + 1);
      if (cat == 6) return idx == 2 ? 25 : (idx == 1 ? 20 : 0);
      if (cat == 7) return idx == 2 ? 35 : (idx == 1 ? 30 : 0);
      if (cat == 8) return idx == 2 ? 45 : (idx == 1 ? 40 : 0);
      return idx == 1 ? 50 : 0;
    }

    void buildHandsAndKeeps() {
      int hIdx = 0;
      for (int a = 1; a <= 6; ++a) {
        for (int b = a; b <= 6; ++b) {
          for (int c = b; c <= 6; ++c) {
            for (int d = c; d <= 6; ++d) {
              for (int e = d; e <= 6; ++e) {
                hands[hIdx] = {a, b, c, d, e};
                handLookup[a - 1][b - 1][c - 1][d - 1][e - 1] =
                    static_cast<uint8_t>(hIdx);
                hIdx++;
              }
            }
          }
        }
      }

      int kIdx = 0;
      for (int c0 = 0; c0 <= 4; ++c0) {
        for (int c1 = 0; c1 <= 4 - c0; ++c1) {
          for (int c2 = 0; c2 <= 4 - c0 - c1; ++c2) {
            for (int c3 = 0; c3 <= 4 - c0 - c1 - c2; ++c3) {
              for (int c4 = 0; c4 <= 4 - c0 - c1 - c2 - c3; ++c4) {
                for (int c5 = 0; c5 <= 4 - c0 - c1 - c2 - c3 - c4; ++c5) {
                  keepLookup[c0][c1][c2][c3][c4][c5] =
                      static_cast<uint8_t>(kIdx++);
                }
              }
            }
          }
        }
      }

      // Build distinct keep options per hand (masks keeping 0..4 dice)
      for (int h = 0; h < NUM_HANDS; ++h) {
        bool seen[NUM_KEEPS] = {};
        for (int mask = 0; mask < 31; ++mask) { // 31 excludes keeping all 5
          int cnt[6] = {};
          int kept = 0;
          for (int i = 0; i < 5; ++i) {
            if ((mask >> i) & 1) {
              cnt[hands[h][i] - 1]++;
              kept++;
            }
          }
          uint8_t kid = getKeepIdFromCounts(cnt);
          if (!seen[kid]) {
            seen[kid] = true;
            handKeepOpts[h].push_back(
                KeepOption{kid, static_cast<uint8_t>(5 - kept)});
          }
        }
      }
    }

    void buildTransitions() {
      for (int c0 = 0; c0 <= 4; ++c0) {
        for (int c1 = 0; c1 <= 4 - c0; ++c1) {
          for (int c2 = 0; c2 <= 4 - c0 - c1; ++c2) {
            for (int c3 = 0; c3 <= 4 - c0 - c1 - c2; ++c3) {
              for (int c4 = 0; c4 <= 4 - c0 - c1 - c2 - c3; ++c4) {
                for (int c5 = 0; c5 <= 4 - c0 - c1 - c2 - c3 - c4; ++c5) {
                  int kid = keepLookup[c0][c1][c2][c3][c4][c5];
                  std::vector<int> base;
                  int counts[6] = {c0, c1, c2, c3, c4, c5};
                  for (int v = 0; v < 6; ++v) {
                    for (int t = 0; t < counts[v]; ++t) base.push_back(v + 1);
                  }
                  int r = 5 - static_cast<int>(base.size());
                  int totalOutcomes = 1;
                  for (int i = 0; i < r; ++i) totalOutcomes *= 6;

                  int freq[NUM_HANDS] = {};
                  std::array<int, 5> cur{};
                  for (size_t i = 0; i < base.size(); ++i) cur[i] = base[i];

                  auto rec = [&](auto &self, int pos) -> void {
                    if (pos == 5) {
                      freq[getHandId(cur)]++;
                      return;
                    }
                    for (int face = 1; face <= 6; ++face) {
                      cur[pos] = face;
                      self(self, pos + 1);
                    }
                  };
                  rec(rec, static_cast<int>(base.size()));

                  for (int h = 0; h < NUM_HANDS; ++h) {
                    if (freq[h] > 0) {
                      transitions[kid].push_back(Transition{
                          static_cast<uint8_t>(h),
                          static_cast<double>(freq[h]) / totalOutcomes});
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    void buildScoringTables() {
      for (int h = 0; h < NUM_HANDS; ++h) {
        const auto &d = hands[h];
        isDormida[h] = esDormidaHand(d);

        for (int c = 0; c < NUM_CATS; ++c) {
          vuelquePts[h][c] = -1;
          manoPts[h][c] = -1;
        }
        for (int v = 1; v <= 6; ++v) {
          int s = sumaChica(v, d);
          if (s > 0) vuelquePts[h][v - 1] = static_cast<int8_t>(s);
        }
        if (esEscaleraHuevo(d)) vuelquePts[h][6] = 20;
        if (esFullHuevo(d)) vuelquePts[h][7] = 30;
        if (esPokerHuevo(d)) vuelquePts[h][8] = 40;
        if (esGrande(d)) vuelquePts[h][9] = 50;

        if (esEscaleraMano(d)) manoPts[h][6] = 25;
        if (esFullMano(d)) manoPts[h][7] = 35;
        if (esPokerMano(d)) manoPts[h][8] = 45;

        // Precompute distinct useful masks across 1-die and 2-die flips
        std::vector<uint16_t> ums;
        for (int i = 0; i < 5; ++i) {
          auto d1 = d;
          d1[i] = 7 - d1[i];
          uint16_t um1 = usefulMaskOfHand(d1);
          if (std::find(ums.begin(), ums.end(), um1) == ums.end()) {
            ums.push_back(um1);
          }
          for (int j = i + 1; j < 5; ++j) {
            auto d2 = d1;
            d2[j] = 7 - d2[j];
            uint16_t um2 = usefulMaskOfHand(d2);
            if (std::find(ums.begin(), ums.end(), um2) == ums.end()) {
              ums.push_back(um2);
            }
          }
        }
        flipUsefulMasks[h] = std::move(ums);
      }

      // Precompute list of mano hands (escalera, full, poker) with initial Roll 1 probs
      for (const auto &tr : transitions[0]) {
        int h = tr.handId;
        if (manoPts[h][6] >= 0) {
          manoHands.push_back(ManoHandInfo{tr.handId, 1, tr.prob});
        } else if (manoPts[h][7] >= 0) {
          manoHands.push_back(ManoHandInfo{tr.handId, 2, tr.prob});
        } else if (manoPts[h][8] >= 0) {
          manoHands.push_back(ManoHandInfo{tr.handId, 4, tr.prob});
        }
      }
    }

    double evalW2WithFloor(int stateId, double floorVal,
                           const std::array<double, NUM_HANDS> &bVuelque,
                           const std::array<double, NUM_HANDS> &bFull,
                           const std::array<double, NUM_CATS> &vNext,
                           double *outKeepEV = nullptr) const {
      int baseState = stateId >> 3;
      int rMask = stateId & 7;
      uint16_t m10 = openMask10(baseState);
      double qPartial[NUM_HANDS];
      double qFull[NUM_HANDS];
      for (int h = 0; h < NUM_HANDS; ++h) {
        double bv = bVuelque[h];
        double bf = bFull[h];
        qPartial[h] = bv > floorVal ? bv : floorVal;
        qFull[h] = bf > floorVal ? bf : floorVal;
      }

      double keepEV[NUM_KEEPS];
      {
        double ev = 0.0;
        for (const auto &tr : transitions[0]) {
          ev += tr.prob * qFull[tr.handId];
        }
        keepEV[0] = ev;
      }
      for (int k = 1; k < NUM_KEEPS; ++k) {
        double ev = 0.0;
        for (const auto &tr : transitions[k]) {
          ev += tr.prob * qPartial[tr.handId];
        }
        keepEV[k] = ev;
      }
      if (outKeepEV) {
        for (int k = 0; k < NUM_KEEPS; ++k) {
          outKeepEV[k] = keepEV[k];
        }
      }

      double baseBest[NUM_HANDS];
      double baseTotal = 0.0;
      for (const auto &tr : transitions[0]) {
        int h = tr.handId;
        double best = -1e18;
        for (const auto &opt : handKeepOpts[h]) {
          if (keepEV[opt.keepId] > best) best = keepEV[opt.keepId];
        }
        for (int c = 6; c <= 8; ++c) {
          if ((m10 & (1u << c)) && manoPts[h][c] >= 0) {
            double val = manoPts[h][c] + vNext[c];
            if (val > best) best = val;
          }
        }
        baseBest[h] = best;
        baseTotal += tr.prob * best;
      }

      int avail = availRespMask(baseState, rMask);
      if (avail == 0) return baseTotal;

      // Exact backward induction over subsets of available respeta flags
      double w2[8] = {};
      w2[0] = baseTotal;
      for (int sub = 1; sub <= avail; ++sub) {
        if ((sub & ~avail) != 0) continue;
        double delta = 0.0;
        for (const auto &mh : manoHands) {
          if (sub & mh.respBit) {
            double respVal = w2[sub ^ mh.respBit];
            if (respVal > baseBest[mh.handId]) {
              delta += mh.prob * (respVal - baseBest[mh.handId]);
            }
          }
        }
        w2[sub] = baseTotal + delta;
      }
      return w2[avail];
    }

    void solveDP() {
      V.assign(NUM_STATES, 0.0);
      W2_yaAn.assign(NUM_STATES, 0.0);
      sobreVal.resize(NUM_STATES);
      bestVuelque.resize(NUM_STATES);
      bestFullReroll.resize(NUM_STATES);
      keepEV1Table.resize(NUM_STATES);
      keepEV2YaAnTable.resize(NUM_STATES);

      std::vector<std::vector<int>> baseByLen(12);
      for (int bs = 0; bs < NUM_BASE_STATES; ++bs) {
        int mask9 = bs / 3;
        int gCount = bs % 3;
        int cnt = __builtin_popcount(static_cast<unsigned>(mask9)) + gCount;
        baseByLen[cnt].push_back(bs);
      }

      // Order rMasks by descending popcount so states with fewer available respetas are solved first
      int rMasksByPopDesc[8] = {7, 3, 5, 6, 1, 2, 4, 0};

      for (int rMask = 0; rMask < 8; ++rMask) {
        for (int h = 0; h < NUM_HANDS; ++h) {
          bestVuelque[rMask][h] = 0.0;
          bestFullReroll[rMask][h] = 0.0;
        }
      }

      for (int len = 1; len <= 11; ++len) {
        for (int bs : baseByLen[len]) {
          uint16_t m10 = openMask10(bs);

          for (int rIdx = 0; rIdx < 8; ++rIdx) {
            int rMask = rMasksByPopDesc[rIdx];
            if (!isValidState(bs, rMask)) continue;

            int s = (bs << 3) | rMask;

            std::array<double, NUM_CATS> vNext{};
            std::array<double, NUM_CATS> w2Next{};
            for (int c = 0; c < NUM_CATS; ++c) {
              if (m10 & (1u << c)) {
                int ns = nextState(s, c);
                vNext[c] = V[ns];
                w2Next[c] = W2_yaAn[ns];
              }
            }

            // 1. Precompute base Q2 values (for Attempt 2)
            auto &bv = bestVuelque[s];
            auto &bf = bestFullReroll[s];
            for (int h = 0; h < NUM_HANDS; ++h) {
              bool borres = inclBorres(m10, h);
              double bestV = -1e18;
              for (int c = 0; c < NUM_CATS; ++c) {
                if (!(m10 & (1u << c))) continue;
                int pts = vuelquePts[h][c];
                if (pts >= 0 || borres) {
                  double val = (pts >= 0 ? pts : 0) + vNext[c];
                  if (val > bestV) bestV = val;
                }
              }
              double bestF = bestV;
              for (int c = 6; c <= 8; ++c) {
                if ((m10 & (1u << c)) && manoPts[h][c] >= 0) {
                  double val = manoPts[h][c] + vNext[c];
                  if (val > bestF) bestF = val;
                }
              }
              bv[h] = bestV;
              bf[h] = bestF;
            }

            // 2. Compute sobreVal[s][c][idx] for Attempt 1 sobre choices
            for (int c = 0; c < NUM_CATS; ++c) {
              if (!(m10 & (1u << c))) continue;
              int nVals = numScoreVals(c);
              for (int idx = 0; idx < nVals; ++idx) {
                int p = idxToScore(c, idx);
                double floorF = p + vNext[c];
                sobreVal[s][c][idx] =
                    evalW2WithFloor(s, floorF, bv, bf, vNext);
              }
            }

            // 3. Compute Attempt 1 value V[s]
            double q1Partial[NUM_HANDS];
            double q1Full[NUM_HANDS];
            for (int h = 0; h < NUM_HANDS; ++h) {
              bool borres = inclBorres(m10, h);
              double b1 = -1e18;
              for (int c = 0; c < NUM_CATS; ++c) {
                if (!(m10 & (1u << c))) continue;
                int pts = vuelquePts[h][c];
                if (pts >= 0 || borres) {
                  int actualPts = pts >= 0 ? pts : 0;
                  double vAnotar = actualPts + w2Next[c];
                  double vSobre = sobreVal[s][c][scoreToIdx(c, actualPts)];
                  double m = vAnotar > vSobre ? vAnotar : vSobre;
                  if (m > b1) b1 = m;
                }
              }
              q1Partial[h] = b1;

              double b1Full = b1;
              for (int c = 6; c <= 8; ++c) {
                if ((m10 & (1u << c)) && manoPts[h][c] >= 0) {
                  int p = manoPts[h][c];
                  double vAnotar = p + w2Next[c];
                  double vSobre = sobreVal[s][c][scoreToIdx(c, p)];
                  double m = vAnotar > vSobre ? vAnotar : vSobre;
                  if (m > b1Full) b1Full = m;
                }
              }
              q1Full[h] = b1Full;
            }

            double keepEV1[NUM_KEEPS];
            {
              double ev = 0.0;
              for (const auto &tr : transitions[0]) {
                ev += tr.prob * q1Full[tr.handId];
              }
              keepEV1[0] = ev;
            }
            for (int k = 1; k < NUM_KEEPS; ++k) {
              double ev = 0.0;
              for (const auto &tr : transitions[k]) {
                ev += tr.prob * q1Partial[tr.handId];
              }
              keepEV1[k] = ev;
            }
            for (int k = 0; k < NUM_KEEPS; ++k) {
              keepEV1Table[s][k] = keepEV1[k];
            }

            int avail = availRespMask(bs, rMask);
            double vSum = 0.0;
            for (const auto &tr : transitions[0]) {
              int h = tr.handId;
              double best = -1e18;
              for (const auto &opt : handKeepOpts[h]) {
                if (keepEV1[opt.keepId] > best) best = keepEV1[opt.keepId];
              }
              for (int c = 6; c <= 8; ++c) {
                if ((m10 & (1u << c)) && manoPts[h][c] >= 0) {
                  int p = manoPts[h][c];
                  double vAnotar = p + w2Next[c];
                  double vSobre = sobreVal[s][c][scoreToIdx(c, p)];
                  double m = vAnotar > vSobre ? vAnotar : vSobre;
                  if (m > best) best = m;
                } else if ((avail & (1 << (c - 6))) && manoPts[h][c] >= 0) {
                  double respVal = V[s | (1 << (c - 6))];
                  if (respVal > best) best = respVal;
                }
              }
              vSum += tr.prob * best;
            }
            V[s] = vSum;

            // 4. Compute W2_yaAn[s] using V[s] (skip len == 11 as Attempt 2 never has all 11)
            if (len < 11) {
              W2_yaAn[s] = evalW2WithFloor(s, V[s], bv, bf, vNext,
                                           keepEV2YaAnTable[s].data());
            }
          }
        }
      }
    }
  };

  static const DPModel &getModel() {
    static DPModel model;
    return model;
  }

  static int categoryIndex(const std::string &rawName) {
    std::string j = rawName;
    size_t pos = j.find(" (de la 1ra mano)");
    if (pos != std::string::npos) j = j.substr(0, pos);
    if (j == "balas") return 0;
    if (j == "tontos") return 1;
    if (j == "trenes") return 2;
    if (j == "cuadras") return 3;
    if (j == "quinas") return 4;
    if (j == "senas") return 5;
    if (j == "escalera") return 6;
    if (j == "full") return 7;
    if (j == "poker") return 8;
    if (j == "grande" || j == "grande2") return 9;
    return -1;
  }

  static int respetaBit(const std::string &juego) {
    if (juego == "escalera") return 1;
    if (juego == "full") return 2;
    if (juego == "poker") return 4;
    return 0;
  }

  static int stateFromMarcador(const Marcador &marc) {
    static const char *names[9] = {"balas",   "tontos",   "trenes",
                                   "cuadras", "quinas",   "senas",
                                   "escalera","full",     "poker"};
    int mask9 = 0;
    for (int i = 0; i < 9; ++i) {
      if (!marc.yaAnotado(names[i])) mask9 |= (1 << i);
    }
    int gCount = (!marc.yaAnotado("grande") ? 1 : 0) +
                 (!marc.yaAnotado("grande2") ? 1 : 0);
    int rMask = 0;
    if ((mask9 & (1 << 6)) == 0 && marc.escaleraRespetada) rMask |= 1;
    if ((mask9 & (1 << 7)) == 0 && marc.fullRespetado) rMask |= 2;
    if ((mask9 & (1 << 8)) == 0 && marc.pokerRespetado) rMask |= 4;
    return ((mask9 * 3 + gCount) << 3) | rMask;
  }

  int lastTurno = -1;
  bool inAttempt2 = false;
  bool yaAnotadoTurn = false;

public:
  JugadorOptimo(std::string nom = "JugadorOptimo") : Jugador(nom) {
    // Ensure DP model is initialized on construction
    (void)getModel();
  }

  double getExpectedInitialScore() const {
    return getModel().V[(NUM_BASE_STATES - 1) << 3];
  }

  int jugar(const std::map<std::string, Marcador> &marcadores,
            const std::vector<Actuacion> &actuacionesPosibles,
            const std::vector<int> &dados,
            const Anotacion &resultadoPrevio) override {
    if (actuacionesPosibles.empty()) return 0;

    // Track attempt & yaAn state reliably
    if (turno != lastTurno) {
      lastTurno = turno;
      inAttempt2 = false;
      yaAnotadoTurn = false;
    }
    if (actuacionesPosibles.size() == 1 &&
        actuacionesPosibles[0].accion == "lanzar") {
      return 0;
    }
    if (resultadoPrevio.puntos != -1) {
      inAttempt2 = true;
      yaAnotadoTurn = false;
    }
    for (const auto &a : actuacionesPosibles) {
      if (a.accion == "nada") {
        inAttempt2 = true;
        yaAnotadoTurn = true;
        break;
      }
      if (a.accion == "sobre") {
        inAttempt2 = false;
        yaAnotadoTurn = false;
        break;
      }
    }

    const DPModel &m = getModel();
    const Marcador &marc = marcadores.at(nombre);
    int stateId = stateFromMarcador(marc);

    const bool isRoll1 = (actuacionesPosibles[0].accion == "lanzar");

    // Precompute floorF if in Attempt 2
    double floorF = m.V[stateId];
    if (inAttempt2 && !yaAnotadoTurn && resultadoPrevio.puntos != -1) {
      int prevCat = categoryIndex(resultadoPrevio.juego);
      if (prevCat >= 0) {
        floorF = resultadoPrevio.puntos +
                 m.V[DPModel::nextState(stateId, prevCat)];
      }
    }

    // If on Roll 1 with sobre floor, compute keepEV lazily; otherwise O(1) lookup
    double keepEV[NUM_KEEPS];
    bool keepComputed[NUM_KEEPS] = {};
    double qPartial[NUM_HANDS];
    const bool usePrecomputedKeep = (!inAttempt2 || yaAnotadoTurn);

    if (isRoll1 && !usePrecomputedKeep) {
      const auto &bv = m.bestVuelque[stateId];
      const auto &bf = m.bestFullReroll[stateId];
      double qFull[NUM_HANDS];
      for (int h = 0; h < NUM_HANDS; ++h) {
        double v1 = bv[h];
        double v2 = bf[h];
        qPartial[h] = v1 > floorF ? v1 : floorF;
        qFull[h] = v2 > floorF ? v2 : floorF;
      }
      keepEV[0] = 0.0;
      for (const auto &tr : m.transitions[0]) {
        keepEV[0] += tr.prob * qFull[tr.handId];
      }
      keepComputed[0] = true;
    }

    auto evalKeep = [&](uint8_t kid) -> double {
      if (!inAttempt2) return m.keepEV1Table[stateId][kid];
      if (yaAnotadoTurn) return m.keepEV2YaAnTable[stateId][kid];
      if (!keepComputed[kid]) {
        double ev = 0.0;
        for (const auto &tr : m.transitions[kid]) {
          ev += tr.prob * qPartial[tr.handId];
        }
        keepEV[kid] = ev;
        keepComputed[kid] = true;
      }
      return keepEV[kid];
    };

    int bestIdx = 0;
    double bestScore = -1e18;

    for (int i = 0; i < static_cast<int>(actuacionesPosibles.size()); ++i) {
      const Actuacion &a = actuacionesPosibles[i];
      double val = -1e18;

      if (a.accion == "dormida") {
        // In Tournament/Anotador, dormida ends the player's game with +0 pts
        val = -1e17;
      } else if (a.accion == "lanzar") {
        if (a.seRespeta) {
          int nextRespState = stateId | respetaBit(a.anotacion.juego);
          if (!inAttempt2) {
            val = m.V[nextRespState];
          } else if (yaAnotadoTurn) {
            val = m.W2_yaAn[nextRespState];
          } else {
            std::array<double, NUM_CATS> vn{};
            uint16_t m10 = DPModel::openMask10(nextRespState >> 3);
            for (int c = 0; c < NUM_CATS; ++c) {
              if (m10 & (1u << c)) {
                vn[c] = m.V[DPModel::nextState(nextRespState, c)];
              }
            }
            val = m.evalW2WithFloor(
                nextRespState, floorF, m.bestVuelque[nextRespState],
                m.bestFullReroll[nextRespState], vn);
          }
        } else {
          int cnt[6] = {};
          bool reroll[5] = {};
          for (int idx : a.indiceDados) reroll[idx] = true;
          for (int d = 0; d < 5; ++d) {
            if (!reroll[d]) cnt[dados[d] - 1]++;
          }
          uint8_t kid = m.getKeepIdFromCounts(cnt);
          val = evalKeep(kid);
        }
      } else if (a.accion == "nada") {
        val = m.V[stateId];
      } else if (a.accion == "anotar" || a.accion == "tachar") {
        int cat = categoryIndex(a.anotacion.juego);
        if (cat >= 0) {
          int ns = DPModel::nextState(stateId, cat);
          if (!inAttempt2) {
            val = a.anotacion.puntos + m.W2_yaAn[ns];
          } else {
            val = a.anotacion.puntos + m.V[ns];
          }
        }
      } else if (a.accion == "sobre") {
        int cat = categoryIndex(a.anotacion.juego);
        if (cat >= 0) {
          int idx = DPModel::scoreToIdx(cat, a.anotacion.puntos);
          val = m.sobreVal[stateId][cat][idx];
        }
      }

      if (val > bestScore) {
        bestScore = val;
        bestIdx = i;
      }
    }

    // Update attempt tracking for our chosen action
    const Actuacion &chosen = actuacionesPosibles[bestIdx];
    if (!inAttempt2 && (chosen.accion == "anotar" || chosen.accion == "tachar" ||
                        chosen.accion == "sobre")) {
      inAttempt2 = true;
      yaAnotadoTurn = (chosen.accion != "sobre");
    }

    return bestIdx;
  }
};

#endif // JUGADOROPTIMO_H
