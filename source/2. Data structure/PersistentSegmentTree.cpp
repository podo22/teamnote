/**
 * [Metadata]
 * Original Author : JusticeHui
 * Source : https://github.com/justiceHui/icpc-teamnote/blob/master/code/DataStructure/PersistentSegmentTree.cpp
 * [Tested on]
 * 
 */
// PST: 구간 k번째 수 (좌표압축 + 버전 배열)
// 1) 값들을 좌표압축 -> 최대값 = 압축 인덱스
// 2) root[0]=new PSTNode; init(root[0], 0, maxC);
// 3) for i=1..n: root[i]=new PSTNode; update(root[i-1], root[i], 0, maxC, a[i]);
// 4) kth(root[l-1], root[r], 0, maxC, k)  -> 구간 [l,r]의 k번째 작은 값(압축idx)
// root[i] = prefix [1..i] 버전. [l,r] = root[r] - root[l-1]
struct PSTNode{
  PSTNode *l, *r; int v;
  PSTNode(){ l = r = nullptr; v = 0; }
};
PSTNode *root[101010];
PST(){ memset(root, 0, sizeof root); } // constructor
void init(PSTNode *node, int s, int e){
  if(s == e) return;
  int m = s + e >> 1;
  node->l = new PSTNode; node->r = new PSTNode;
  init(node->l, s, m); init(node->r, m+1, e);
}
void update(PSTNode *prv, PSTNode *now, int s, int e, int x){
  if (s == e) { now->v = prv ? prv->v + 1 : 1; return; }
  int m = s + e >> 1;
  if (x <= m) {
    now->l = new PSTNode; now->r = prv->r;
    update(prv->l, now->l, s, m, x);
  }
  else {
    now->r = new PSTNode; now->l = prv->l;
    update(prv->r, now->r, m+1, e, x);
  }
  int t1 = now->l ? now->l->v : 0;
  int t2 = now->r ? now->r->v : 0;
  now->v = t1 + t2;
}
int kth(PSTNode *prv, PSTNode *now, int s, int e, int k){
  if (s == e) return s;
  int m = s + e >> 1, diff = now->l->v - prv->l->v;
  if (k <= diff) return kth(prv->l, now->l, s, m, k);
  else return kth(prv->r, now->r, m+1, e, k-diff);
}