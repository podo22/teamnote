/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/Math/bostan_mori.cpp)
 * [Tested on]
 * 
 */
Mint bostan_mori(FPS P, FPS Q, ll k) {
  // return [x^k] P/Q
  while (k){
    FPS Q_(Q.coef);
    for (int i = 1; i <= Q_.deg(); i+=2) {
      Q_.coef[i] *= Mint(-1);
    }
    P *= Q_; Q *= Q_;
    Poly tmp;
    for (int i = k%2; i <= P.deg(); i+=2) {
      tmp.push_back(P.coef[i]);
    }
    P = FPS(tmp);
    tmp.clear();
    for (int i = 0; i <= Q.deg(); i+=2) {
      tmp.push_back(Q.coef[i]);
    }
    Q = FPS(tmp);
    k /= 2;
  }
  return P.evaluate(0) / Q.evaluate(0);
}