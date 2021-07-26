#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
using namespace std;

int histogram[100000];

int dac(int lo, int hi);
int getMaxIncludeMid(int lo, int hi, int mid);

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &histogram[i]);
	}

	printf("%d", dac(0, N));
}

int dac(int lo, int hi) {
	if (lo == hi) return 0;
	if (lo + 1 == hi) return histogram[lo];
	int mid = (lo + hi) / 2;

	int ret = max(dac(lo, mid), dac(mid + 1, hi));
	//printf("side: %d\n", ret);
	int midInclude = getMaxIncludeMid(lo, hi, mid);
	//printf("midInclude: %d\n", midInclude);
	ret = max(ret, midInclude);
	//printf("(%d~%d): %d\n", lo, hi-1, ret);

	return ret;
}

int getMaxIncludeMid(int lo, int hi, int mid) {
	int sl = mid;
	int sh = mid + 1;

	int maxSize = histogram[mid];
	int minHeight = histogram[mid];
	while (sl > lo || sh < hi) {
		if (sl == lo) {
			minHeight = min(minHeight, histogram[sh]);
			sh++;
		}
		else if (sh == hi) {
			minHeight = min(minHeight, histogram[sl - 1]);
			sl--;
		}
		else {
			if(histogram[sl - 1] > histogram[sh]) {
				minHeight = min(minHeight, histogram[sl - 1]);
				sl--;
			}
			else {
				minHeight = min(minHeight, histogram[sh]);
				sh++;
			}
		}
		int width = sh - sl;
		maxSize = max(
			maxSize,
			minHeight * width);
		//printf("(%d~%d): %d\n", sl, sh-1, maxSize);
	}
	return maxSize;
}