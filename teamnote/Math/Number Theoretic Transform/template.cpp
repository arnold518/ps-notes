// mint must be included

namespace NTT
{
    const mint G; // primitive root of MOD

    const int MAXB;
    const int MAXN = (1<<MAXB); // MAXN must divide MOD-1

    void init() {}

    // Get DFT (IDFT if inv is true) of polynomial A
    // length of A must be power of 2
	void dft(vector<mint> &A, bool inv) {}

    // Multiplies polynomial F, G
	vector<mint> multiply(vector<mint> F, vector<mint> G) {}
};