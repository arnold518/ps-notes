namespace FFT
{
    // double (double_range : 2^52) <=> long double (double_range : 2^63)
    // ll (long_range : 2^63) <=> dll (long_range : 2^128)

	typedef complex<double> cpx;
    const double PI = acos((double)-1);

    const int MAXB = 21;
    const int MAXN = (1<<MAXB);

    vector<cpx> W;
    vector<int> rev;
    void init() {}

    // Get DFT (IDFT if inv is true) of polynomial A
    // length of A must be power of 2
	void dft(vector<cpx> &A, bool inv) {}

    // Multiplies polynomial F, G (MAXV is small)
    // MAXV * MAXV * N <= long_range
    // MAXV * MAXV * N <= double_range
	vector<ll> multiply(vector<int> F, vector<int> G) {}

    const int D = 4e4; // sqrt(MAXV)
    // Multiplies polynomial F, G (MAXV is big)
    // MAXV * MAXV * N <= long_range
    // D * D * N = MAXV * N <= double_range
    vector<ll> multiply2(vector<int> F, vector<int> G) {}
};