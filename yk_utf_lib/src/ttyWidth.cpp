#include <Yk/utf/ttyWidth.hpp>

#include <vector>
#include <iostream>
#include <algorithm>

namespace Yk{
namespace UTF{

	struct TTYWidthData {
		char32_t codePoint;
		size_t ttyWidth;
		bool operator<(const TTYWidthData& arg)const{
			return codePoint < arg.codePoint;
		}
		bool operator<(char32_t cp)const{
			return codePoint < cp;
		}
		friend bool operator<(char32_t arg1, const TTYWidthData& arg2){
			return arg1 < arg2.codePoint;
		}
	};

	std::vector<TTYWidthData> ttyWidthDataList = {
		{0x00, 0},
		{0x20, 1},
		{0x7f, 0},
		{0xa0, 1},
		{0xa1, 2},
		{0xa2, 1},
		{0xa4, 2},
		{0xa5, 1},
		{0xa7, 2},
		{0xa9, 1},
		{0xaa, 2},
		{0xab, 1},
		{0xae, 2},
		{0xaf, 1},
		{0xb0, 2},
		{0xb5, 1},
		{0xb6, 2},
		{0xbb, 1},
		{0xbc, 2},
		{0xc0, 1},
		{0xc6, 2},
		{0xc7, 1},
		{0xd0, 2},
		{0xd1, 1},
		{0xd7, 2},
		{0xd9, 1},
		{0xde, 2},
		{0xe2, 1},
		{0xe6, 2},
		{0xe7, 1},
		{0xe8, 2},
		{0xeb, 1},
		{0xec, 2},
		{0xee, 1},
		{0xf0, 2},
		{0xf1, 1},
		{0xf2, 2},
		{0xf4, 1},
		{0xf7, 2},
		{0xfb, 1},
		{0xfc, 2},
		{0xfd, 1},
		{0xfe, 2},
		{0xff, 1},
		{0x101, 2},
		{0x102, 1},
		{0x111, 2},
		{0x112, 1},
		{0x113, 2},
		{0x114, 1},
		{0x11b, 2},
		{0x11c, 1},
		{0x126, 2},
		{0x128, 1},
		{0x12b, 2},
		{0x12c, 1},
		{0x131, 2},
		{0x134, 1},
		{0x138, 2},
		{0x139, 1},
		{0x13f, 2},
		{0x143, 1},
		{0x144, 2},
		{0x145, 1},
		{0x148, 2},
		{0x14c, 1},
		{0x14d, 2},
		{0x14e, 1},
		{0x152, 2},
		{0x154, 1},
		{0x166, 2},
		{0x168, 1},
		{0x16b, 2},
		{0x16c, 1},
		{0x1ce, 2},
		{0x1cf, 1},
		{0x1d0, 2},
		{0x1d1, 1},
		{0x1d2, 2},
		{0x1d3, 1},
		{0x1d4, 2},
		{0x1d5, 1},
		{0x1d6, 2},
		{0x1d7, 1},
		{0x1d8, 2},
		{0x1d9, 1},
		{0x1da, 2},
		{0x1db, 1},
		{0x1dc, 2},
		{0x1dd, 1},
		{0x251, 2},
		{0x252, 1},
		{0x261, 2},
		{0x262, 1},
		{0x2c4, 2},
		{0x2c5, 1},
		{0x2c7, 2},
		{0x2c8, 1},
		{0x2c9, 2},
		{0x2cc, 1},
		{0x2cd, 2},
		{0x2ce, 1},
		{0x2d0, 2},
		{0x2d1, 1},
		{0x2d8, 2},
		{0x2dc, 1},
		{0x2dd, 2},
		{0x2de, 1},
		{0x2df, 2},
		{0x2e0, 1},
		{0x300, 0},
		{0x370, 1},
		{0x391, 2},
		{0x3a2, 1},
		{0x3a3, 2},
		{0x3aa, 1},
		{0x3b1, 2},
		{0x3c2, 1},
		{0x3c3, 2},
		{0x3ca, 1},
		{0x401, 2},
		{0x402, 1},
		{0x410, 2},
		{0x450, 1},
		{0x451, 2},
		{0x452, 1},
		{0x483, 0},
		{0x48a, 1},
		{0x591, 0},
		{0x5be, 1},
		{0x5bf, 0},
		{0x5c0, 1},
		{0x5c1, 0},
		{0x5c3, 1},
		{0x5c4, 0},
		{0x5c6, 1},
		{0x5c7, 0},
		{0x5c8, 1},
		{0x600, 0},
		{0x606, 1},
		{0x610, 0},
		{0x61b, 1},
		{0x61c, 0},
		{0x61d, 1},
		{0x64b, 0},
		{0x660, 1},
		{0x670, 0},
		{0x671, 1},
		{0x6d6, 0},
		{0x6de, 1},
		{0x6df, 0},
		{0x6e5, 1},
		{0x6e7, 0},
		{0x6e9, 1},
		{0x6ea, 0},
		{0x6ee, 1},
		{0x70f, 0},
		{0x710, 1},
		{0x711, 0},
		{0x712, 1},
		{0x730, 0},
		{0x74b, 1},
		{0x7a6, 0},
		{0x7b1, 1},
		{0x7eb, 0},
		{0x7f4, 1},
		{0x7fd, 0},
		{0x7fe, 1},
		{0x816, 0},
		{0x81a, 1},
		{0x81b, 0},
		{0x824, 1},
		{0x825, 0},
		{0x828, 1},
		{0x829, 0},
		{0x82e, 1},
		{0x859, 0},
		{0x85c, 1},
		{0x8d3, 0},
		{0x903, 1},
		{0x93a, 0},
		{0x93b, 1},
		{0x93c, 0},
		{0x93d, 1},
		{0x941, 0},
		{0x949, 1},
		{0x94d, 0},
		{0x94e, 1},
		{0x951, 0},
		{0x958, 1},
		{0x962, 0},
		{0x964, 1},
		{0x981, 0},
		{0x982, 1},
		{0x9bc, 0},
		{0x9bd, 1},
		{0x9c1, 0},
		{0x9c5, 1},
		{0x9cd, 0},
		{0x9ce, 1},
		{0x9e2, 0},
		{0x9e4, 1},
		{0x9fe, 0},
		{0x9ff, 1},
		{0xa01, 0},
		{0xa03, 1},
		{0xa3c, 0},
		{0xa3d, 1},
		{0xa41, 0},
		{0xa43, 1},
		{0xa47, 0},
		{0xa49, 1},
		{0xa4b, 0},
		{0xa4e, 1},
		{0xa51, 0},
		{0xa52, 1},
		{0xa70, 0},
		{0xa72, 1},
		{0xa75, 0},
		{0xa76, 1},
		{0xa81, 0},
		{0xa83, 1},
		{0xabc, 0},
		{0xabd, 1},
		{0xac1, 0},
		{0xac6, 1},
		{0xac7, 0},
		{0xac9, 1},
		{0xacd, 0},
		{0xace, 1},
		{0xae2, 0},
		{0xae4, 1},
		{0xafa, 0},
		{0xb00, 1},
		{0xb01, 0},
		{0xb02, 1},
		{0xb3c, 0},
		{0xb3d, 1},
		{0xb3f, 0},
		{0xb40, 1},
		{0xb41, 0},
		{0xb45, 1},
		{0xb4d, 0},
		{0xb4e, 1},
		{0xb56, 0},
		{0xb57, 1},
		{0xb62, 0},
		{0xb64, 1},
		{0xb82, 0},
		{0xb83, 1},
		{0xbc0, 0},
		{0xbc1, 1},
		{0xbcd, 0},
		{0xbce, 1},
		{0xc00, 0},
		{0xc01, 1},
		{0xc04, 0},
		{0xc05, 1},
		{0xc3e, 0},
		{0xc41, 1},
		{0xc46, 0},
		{0xc49, 1},
		{0xc4a, 0},
		{0xc4e, 1},
		{0xc55, 0},
		{0xc57, 1},
		{0xc62, 0},
		{0xc64, 1},
		{0xc81, 0},
		{0xc82, 1},
		{0xcbc, 0},
		{0xcbd, 1},
		{0xcbf, 0},
		{0xcc0, 1},
		{0xcc6, 0},
		{0xcc7, 1},
		{0xccc, 0},
		{0xcce, 1},
		{0xce2, 0},
		{0xce4, 1},
		{0xd00, 0},
		{0xd02, 1},
		{0xd3b, 0},
		{0xd3d, 1},
		{0xd41, 0},
		{0xd45, 1},
		{0xd4d, 0},
		{0xd4e, 1},
		{0xd62, 0},
		{0xd64, 1},
		{0xdca, 0},
		{0xdcb, 1},
		{0xdd2, 0},
		{0xdd5, 1},
		{0xdd6, 0},
		{0xdd7, 1},
		{0xe31, 0},
		{0xe32, 1},
		{0xe34, 0},
		{0xe3b, 1},
		{0xe47, 0},
		{0xe4f, 1},
		{0xeb1, 0},
		{0xeb2, 1},
		{0xeb4, 0},
		{0xeba, 1},
		{0xebb, 0},
		{0xebd, 1},
		{0xec8, 0},
		{0xece, 1},
		{0xf18, 0},
		{0xf1a, 1},
		{0xf35, 0},
		{0xf36, 1},
		{0xf37, 0},
		{0xf38, 1},
		{0xf39, 0},
		{0xf3a, 1},
		{0xf71, 0},
		{0xf7f, 1},
		{0xf80, 0},
		{0xf85, 1},
		{0xf86, 0},
		{0xf88, 1},
		{0xf8d, 0},
		{0xf98, 1},
		{0xf99, 0},
		{0xfbd, 1},
		{0xfc6, 0},
		{0xfc7, 1},
		{0x102d, 0},
		{0x1031, 1},
		{0x1032, 0},
		{0x1038, 1},
		{0x1039, 0},
		{0x103b, 1},
		{0x103d, 0},
		{0x103f, 1},
		{0x1058, 0},
		{0x105a, 1},
		{0x105e, 0},
		{0x1061, 1},
		{0x1071, 0},
		{0x1075, 1},
		{0x1082, 0},
		{0x1083, 1},
		{0x1085, 0},
		{0x1087, 1},
		{0x108d, 0},
		{0x108e, 1},
		{0x109d, 0},
		{0x109e, 1},
		{0x1100, 2},
		{0x1160, 0},
		{0x1200, 1},
		{0x135d, 0},
		{0x1360, 1},
		{0x1712, 0},
		{0x1715, 1},
		{0x1732, 0},
		{0x1735, 1},
		{0x1752, 0},
		{0x1754, 1},
		{0x1772, 0},
		{0x1774, 1},
		{0x17b4, 0},
		{0x17b6, 1},
		{0x17b7, 0},
		{0x17be, 1},
		{0x17c6, 0},
		{0x17c7, 1},
		{0x17c9, 0},
		{0x17d4, 1},
		{0x17dd, 0},
		{0x17de, 1},
		{0x180b, 0},
		{0x180f, 1},
		{0x1885, 0},
		{0x1887, 1},
		{0x18a9, 0},
		{0x18aa, 1},
		{0x1920, 0},
		{0x1923, 1},
		{0x1927, 0},
		{0x1929, 1},
		{0x1932, 0},
		{0x1933, 1},
		{0x1939, 0},
		{0x193c, 1},
		{0x1a17, 0},
		{0x1a19, 1},
		{0x1a1b, 0},
		{0x1a1c, 1},
		{0x1a56, 0},
		{0x1a57, 1},
		{0x1a58, 0},
		{0x1a5f, 1},
		{0x1a60, 0},
		{0x1a61, 1},
		{0x1a62, 0},
		{0x1a63, 1},
		{0x1a65, 0},
		{0x1a6d, 1},
		{0x1a73, 0},
		{0x1a7d, 1},
		{0x1a7f, 0},
		{0x1a80, 1},
		{0x1ab0, 0},
		{0x1abf, 1},
		{0x1b00, 0},
		{0x1b04, 1},
		{0x1b34, 0},
		{0x1b35, 1},
		{0x1b36, 0},
		{0x1b3b, 1},
		{0x1b3c, 0},
		{0x1b3d, 1},
		{0x1b42, 0},
		{0x1b43, 1},
		{0x1b6b, 0},
		{0x1b74, 1},
		{0x1b80, 0},
		{0x1b82, 1},
		{0x1ba2, 0},
		{0x1ba6, 1},
		{0x1ba8, 0},
		{0x1baa, 1},
		{0x1bab, 0},
		{0x1bae, 1},
		{0x1be6, 0},
		{0x1be7, 1},
		{0x1be8, 0},
		{0x1bea, 1},
		{0x1bed, 0},
		{0x1bee, 1},
		{0x1bef, 0},
		{0x1bf2, 1},
		{0x1c2c, 0},
		{0x1c34, 1},
		{0x1c36, 0},
		{0x1c38, 1},
		{0x1cd0, 0},
		{0x1cd3, 1},
		{0x1cd4, 0},
		{0x1ce1, 1},
		{0x1ce2, 0},
		{0x1ce9, 1},
		{0x1ced, 0},
		{0x1cee, 1},
		{0x1cf4, 0},
		{0x1cf5, 1},
		{0x1cf8, 0},
		{0x1cfa, 1},
		{0x1dc0, 0},
		{0x1dfa, 1},
		{0x1dfb, 0},
		{0x1e00, 1},
		{0x200b, 0},
		{0x2010, 2},
		{0x2011, 1},
		{0x2013, 2},
		{0x2017, 1},
		{0x2018, 2},
		{0x201a, 1},
		{0x201c, 2},
		{0x201e, 1},
		{0x2020, 2},
		{0x2023, 1},
		{0x2024, 2},
		{0x2028, 1},
		{0x202a, 0},
		{0x202f, 1},
		{0x2030, 2},
		{0x2031, 1},
		{0x2032, 2},
		{0x2034, 1},
		{0x2035, 2},
		{0x2036, 1},
		{0x203b, 2},
		{0x203c, 1},
		{0x203e, 2},
		{0x203f, 1},
		{0x2060, 0},
		{0x2065, 1},
		{0x2066, 0},
		{0x2070, 1},
		{0x2074, 2},
		{0x2075, 1},
		{0x207f, 2},
		{0x2080, 1},
		{0x2081, 2},
		{0x2085, 1},
		{0x20ac, 2},
		{0x20ad, 1},
		{0x20d0, 0},
		{0x20f1, 1},
		{0x2103, 2},
		{0x2104, 1},
		{0x2105, 2},
		{0x2106, 1},
		{0x2109, 2},
		{0x210a, 1},
		{0x2113, 2},
		{0x2114, 1},
		{0x2116, 2},
		{0x2117, 1},
		{0x2121, 2},
		{0x2123, 1},
		{0x2126, 2},
		{0x2127, 1},
		{0x212b, 2},
		{0x212c, 1},
		{0x2153, 2},
		{0x2155, 1},
		{0x215b, 2},
		{0x215f, 1},
		{0x2160, 2},
		{0x216c, 1},
		{0x2170, 2},
		{0x217a, 1},
		{0x2189, 2},
		{0x218a, 1},
		{0x2190, 2},
		{0x219a, 1},
		{0x21b8, 2},
		{0x21ba, 1},
		{0x21d2, 2},
		{0x21d3, 1},
		{0x21d4, 2},
		{0x21d5, 1},
		{0x21e7, 2},
		{0x21e8, 1},
		{0x2200, 2},
		{0x2201, 1},
		{0x2202, 2},
		{0x2204, 1},
		{0x2207, 2},
		{0x2209, 1},
		{0x220b, 2},
		{0x220c, 1},
		{0x220f, 2},
		{0x2210, 1},
		{0x2211, 2},
		{0x2212, 1},
		{0x2215, 2},
		{0x2216, 1},
		{0x221a, 2},
		{0x221b, 1},
		{0x221d, 2},
		{0x2221, 1},
		{0x2223, 2},
		{0x2224, 1},
		{0x2225, 2},
		{0x2226, 1},
		{0x2227, 2},
		{0x222d, 1},
		{0x222e, 2},
		{0x222f, 1},
		{0x2234, 2},
		{0x2238, 1},
		{0x223c, 2},
		{0x223e, 1},
		{0x2248, 2},
		{0x2249, 1},
		{0x224c, 2},
		{0x224d, 1},
		{0x2252, 2},
		{0x2253, 1},
		{0x2260, 2},
		{0x2262, 1},
		{0x2264, 2},
		{0x2268, 1},
		{0x226a, 2},
		{0x226c, 1},
		{0x226e, 2},
		{0x2270, 1},
		{0x2282, 2},
		{0x2284, 1},
		{0x2286, 2},
		{0x2288, 1},
		{0x2295, 2},
		{0x2296, 1},
		{0x2299, 2},
		{0x229a, 1},
		{0x22a5, 2},
		{0x22a6, 1},
		{0x22bf, 2},
		{0x22c0, 1},
		{0x2312, 2},
		{0x2313, 1},
		{0x231a, 2},
		{0x231c, 1},
		{0x2329, 2},
		{0x232b, 1},
		{0x23e9, 2},
		{0x23ed, 1},
		{0x23f0, 2},
		{0x23f1, 1},
		{0x23f3, 2},
		{0x23f4, 1},
		{0x2460, 2},
		{0x24ea, 1},
		{0x24eb, 2},
		{0x254c, 1},
		{0x2550, 2},
		{0x2574, 1},
		{0x2580, 2},
		{0x2590, 1},
		{0x2592, 2},
		{0x2596, 1},
		{0x25a0, 2},
		{0x25a2, 1},
		{0x25a3, 2},
		{0x25aa, 1},
		{0x25b2, 2},
		{0x25b4, 1},
		{0x25b6, 2},
		{0x25b8, 1},
		{0x25bc, 2},
		{0x25be, 1},
		{0x25c0, 2},
		{0x25c2, 1},
		{0x25c6, 2},
		{0x25c9, 1},
		{0x25cb, 2},
		{0x25cc, 1},
		{0x25ce, 2},
		{0x25d2, 1},
		{0x25e2, 2},
		{0x25e6, 1},
		{0x25ef, 2},
		{0x25f0, 1},
		{0x25fd, 2},
		{0x25ff, 1},
		{0x2605, 2},
		{0x2607, 1},
		{0x2609, 2},
		{0x260a, 1},
		{0x260e, 2},
		{0x2610, 1},
		{0x2614, 2},
		{0x2616, 1},
		{0x261c, 2},
		{0x261d, 1},
		{0x261e, 2},
		{0x261f, 1},
		{0x2640, 2},
		{0x2641, 1},
		{0x2642, 2},
		{0x2643, 1},
		{0x2648, 2},
		{0x2654, 1},
		{0x2660, 2},
		{0x2662, 1},
		{0x2663, 2},
		{0x2666, 1},
		{0x2667, 2},
		{0x266b, 1},
		{0x266c, 2},
		{0x266e, 1},
		{0x266f, 2},
		{0x2670, 1},
		{0x267f, 2},
		{0x2680, 1},
		{0x2693, 2},
		{0x2694, 1},
		{0x269e, 2},
		{0x26a0, 1},
		{0x26a1, 2},
		{0x26a2, 1},
		{0x26aa, 2},
		{0x26ac, 1},
		{0x26bd, 2},
		{0x26c0, 1},
		{0x26c4, 2},
		{0x26e2, 1},
		{0x26e3, 2},
		{0x26e4, 1},
		{0x26e8, 2},
		{0x2700, 1},
		{0x2705, 2},
		{0x2706, 1},
		{0x270a, 2},
		{0x270c, 1},
		{0x2728, 2},
		{0x2729, 1},
		{0x273d, 2},
		{0x273e, 1},
		{0x274c, 2},
		{0x274d, 1},
		{0x274e, 2},
		{0x274f, 1},
		{0x2753, 2},
		{0x2756, 1},
		{0x2757, 2},
		{0x2758, 1},
		{0x2776, 2},
		{0x2780, 1},
		{0x2795, 2},
		{0x2798, 1},
		{0x27b0, 2},
		{0x27b1, 1},
		{0x27bf, 2},
		{0x27c0, 1},
		{0x2b1b, 2},
		{0x2b1d, 1},
		{0x2b50, 2},
		{0x2b51, 1},
		{0x2b55, 2},
		{0x2b5a, 1},
		{0x2cef, 0},
		{0x2cf2, 1},
		{0x2d7f, 0},
		{0x2d80, 1},
		{0x2de0, 0},
		{0x2e00, 1},
		{0x2e80, 2},
		{0x302a, 0},
		{0x302e, 2},
		{0x303f, 1},
		{0x3040, 2},
		{0x3099, 0},
		{0x309b, 2},
		{0x321f, 1},
		{0x3220, 2},
		{0x32ff, 1},
		{0x3300, 2},
		{0x4dc0, 1},
		{0x4e00, 2},
		{0xa4d0, 1},
		{0xa66f, 0},
		{0xa673, 1},
		{0xa674, 0},
		{0xa67e, 1},
		{0xa69e, 0},
		{0xa6a0, 1},
		{0xa6f0, 0},
		{0xa6f2, 1},
		{0xa802, 0},
		{0xa803, 1},
		{0xa806, 0},
		{0xa807, 1},
		{0xa80b, 0},
		{0xa80c, 1},
		{0xa825, 0},
		{0xa827, 1},
		{0xa8c4, 0},
		{0xa8c6, 1},
		{0xa8e0, 0},
		{0xa8f2, 1},
		{0xa8ff, 0},
		{0xa900, 1},
		{0xa926, 0},
		{0xa92e, 1},
		{0xa947, 0},
		{0xa952, 1},
		{0xa960, 2},
		{0xa980, 0},
		{0xa983, 1},
		{0xa9b3, 0},
		{0xa9b4, 1},
		{0xa9b6, 0},
		{0xa9ba, 1},
		{0xa9bc, 0},
		{0xa9bd, 1},
		{0xa9e5, 0},
		{0xa9e6, 1},
		{0xaa29, 0},
		{0xaa2f, 1},
		{0xaa31, 0},
		{0xaa33, 1},
		{0xaa35, 0},
		{0xaa37, 1},
		{0xaa43, 0},
		{0xaa44, 1},
		{0xaa4c, 0},
		{0xaa4d, 1},
		{0xaa7c, 0},
		{0xaa7d, 1},
		{0xaab0, 0},
		{0xaab1, 1},
		{0xaab2, 0},
		{0xaab5, 1},
		{0xaab7, 0},
		{0xaab9, 1},
		{0xaabe, 0},
		{0xaac0, 1},
		{0xaac1, 0},
		{0xaac2, 1},
		{0xaaec, 0},
		{0xaaee, 1},
		{0xaaf6, 0},
		{0xaaf7, 1},
		{0xabe5, 0},
		{0xabe6, 1},
		{0xabe8, 0},
		{0xabe9, 1},
		{0xabed, 0},
		{0xabee, 1},
		{0xac00, 2},
		{0xd7b0, 0},
		{0xd7c7, 1},
		{0xd7cb, 0},
		{0xd7fc, 1},
		{0xd800, 0},
		{0xe000, 2},
		{0xfb00, 1},
		{0xfb1e, 0},
		{0xfb1f, 1},
		{0xfe00, 0},
		{0xfe10, 2},
		{0xfe20, 0},
		{0xfe30, 2},
		{0xfe70, 1},
		{0xfeff, 0},
		{0xff00, 1},
		{0xff01, 2},
		{0xff61, 1},
		{0xffe0, 2},
		{0xffe7, 1},
		{0xfff9, 0},
		{0xfffc, 1},
		{0xfffd, 2},
		{0xfffe, 1},
		{0x101fd, 0},
		{0x101fe, 1},
		{0x102e0, 0},
		{0x102e1, 1},
		{0x10376, 0},
		{0x1037b, 1},
		{0x10a01, 0},
		{0x10a04, 1},
		{0x10a05, 0},
		{0x10a07, 1},
		{0x10a0c, 0},
		{0x10a10, 1},
		{0x10a38, 0},
		{0x10a3b, 1},
		{0x10a3f, 0},
		{0x10a40, 1},
		{0x10ae5, 0},
		{0x10ae7, 1},
		{0x10d24, 0},
		{0x10d28, 1},
		{0x10f46, 0},
		{0x10f51, 1},
		{0x11001, 0},
		{0x11002, 1},
		{0x11038, 0},
		{0x11047, 1},
		{0x1107f, 0},
		{0x11082, 1},
		{0x110b3, 0},
		{0x110b7, 1},
		{0x110b9, 0},
		{0x110bb, 1},
		{0x110bd, 0},
		{0x110be, 1},
		{0x110cd, 0},
		{0x110ce, 1},
		{0x11100, 0},
		{0x11103, 1},
		{0x11127, 0},
		{0x1112c, 1},
		{0x1112d, 0},
		{0x11135, 1},
		{0x11173, 0},
		{0x11174, 1},
		{0x11180, 0},
		{0x11182, 1},
		{0x111b6, 0},
		{0x111bf, 1},
		{0x111c9, 0},
		{0x111cd, 1},
		{0x1122f, 0},
		{0x11232, 1},
		{0x11234, 0},
		{0x11235, 1},
		{0x11236, 0},
		{0x11238, 1},
		{0x1123e, 0},
		{0x1123f, 1},
		{0x112df, 0},
		{0x112e0, 1},
		{0x112e3, 0},
		{0x112eb, 1},
		{0x11300, 0},
		{0x11302, 1},
		{0x1133b, 0},
		{0x1133d, 1},
		{0x11340, 0},
		{0x11341, 1},
		{0x11366, 0},
		{0x1136d, 1},
		{0x11370, 0},
		{0x11375, 1},
		{0x11438, 0},
		{0x11440, 1},
		{0x11442, 0},
		{0x11445, 1},
		{0x11446, 0},
		{0x11447, 1},
		{0x1145e, 0},
		{0x1145f, 1},
		{0x114b3, 0},
		{0x114b9, 1},
		{0x114ba, 0},
		{0x114bb, 1},
		{0x114bf, 0},
		{0x114c1, 1},
		{0x114c2, 0},
		{0x114c4, 1},
		{0x115b2, 0},
		{0x115b6, 1},
		{0x115bc, 0},
		{0x115be, 1},
		{0x115bf, 0},
		{0x115c1, 1},
		{0x115dc, 0},
		{0x115de, 1},
		{0x11633, 0},
		{0x1163b, 1},
		{0x1163d, 0},
		{0x1163e, 1},
		{0x1163f, 0},
		{0x11641, 1},
		{0x116ab, 0},
		{0x116ac, 1},
		{0x116ad, 0},
		{0x116ae, 1},
		{0x116b0, 0},
		{0x116b6, 1},
		{0x116b7, 0},
		{0x116b8, 1},
		{0x1171d, 0},
		{0x11720, 1},
		{0x11722, 0},
		{0x11726, 1},
		{0x11727, 0},
		{0x1172c, 1},
		{0x1182f, 0},
		{0x11838, 1},
		{0x11839, 0},
		{0x1183b, 1},
		{0x11a01, 0},
		{0x11a0b, 1},
		{0x11a33, 0},
		{0x11a39, 1},
		{0x11a3b, 0},
		{0x11a3f, 1},
		{0x11a47, 0},
		{0x11a48, 1},
		{0x11a51, 0},
		{0x11a57, 1},
		{0x11a59, 0},
		{0x11a5c, 1},
		{0x11a8a, 0},
		{0x11a97, 1},
		{0x11a98, 0},
		{0x11a9a, 1},
		{0x11c30, 0},
		{0x11c37, 1},
		{0x11c38, 0},
		{0x11c3e, 1},
		{0x11c3f, 0},
		{0x11c40, 1},
		{0x11c92, 0},
		{0x11ca8, 1},
		{0x11caa, 0},
		{0x11cb1, 1},
		{0x11cb2, 0},
		{0x11cb4, 1},
		{0x11cb5, 0},
		{0x11cb7, 1},
		{0x11d31, 0},
		{0x11d37, 1},
		{0x11d3a, 0},
		{0x11d3b, 1},
		{0x11d3c, 0},
		{0x11d3e, 1},
		{0x11d3f, 0},
		{0x11d46, 1},
		{0x11d47, 0},
		{0x11d48, 1},
		{0x11d90, 0},
		{0x11d92, 1},
		{0x11d95, 0},
		{0x11d96, 1},
		{0x11d97, 0},
		{0x11d98, 1},
		{0x11ef3, 0},
		{0x11ef5, 1},
		{0x16af0, 0},
		{0x16af5, 1},
		{0x16b30, 0},
		{0x16b37, 1},
		{0x16f8f, 0},
		{0x16f93, 1},
		{0x16fe0, 2},
		{0x18b00, 1},
		{0x1b000, 2},
		{0x1b130, 1},
		{0x1b170, 2},
		{0x1b300, 1},
		{0x1bc9d, 0},
		{0x1bc9f, 1},
		{0x1bca0, 0},
		{0x1bca4, 1},
		{0x1d167, 0},
		{0x1d16a, 1},
		{0x1d173, 0},
		{0x1d183, 1},
		{0x1d185, 0},
		{0x1d18c, 1},
		{0x1d1aa, 0},
		{0x1d1ae, 1},
		{0x1d242, 0},
		{0x1d245, 1},
		{0x1da00, 0},
		{0x1da37, 1},
		{0x1da3b, 0},
		{0x1da6d, 1},
		{0x1da75, 0},
		{0x1da76, 1},
		{0x1da84, 0},
		{0x1da85, 1},
		{0x1da9b, 0},
		{0x1daa0, 1},
		{0x1daa1, 0},
		{0x1dab0, 1},
		{0x1e000, 0},
		{0x1e007, 1},
		{0x1e008, 0},
		{0x1e019, 1},
		{0x1e01b, 0},
		{0x1e022, 1},
		{0x1e023, 0},
		{0x1e025, 1},
		{0x1e026, 0},
		{0x1e02b, 1},
		{0x1e8d0, 0},
		{0x1e8d7, 1},
		{0x1e944, 0},
		{0x1e94b, 1},
		{0x1f004, 2},
		{0x1f005, 1},
		{0x1f0cf, 2},
		{0x1f0d0, 1},
		{0x1f100, 2},
		{0x1f10b, 1},
		{0x1f110, 2},
		{0x1f12e, 1},
		{0x1f130, 2},
		{0x1f16a, 1},
		{0x1f170, 2},
		{0x1f1ad, 1},
		{0x1f200, 2},
		{0x1f321, 1},
		{0x1f32d, 2},
		{0x1f336, 1},
		{0x1f337, 2},
		{0x1f37d, 1},
		{0x1f37e, 2},
		{0x1f394, 1},
		{0x1f3a0, 2},
		{0x1f3cb, 1},
		{0x1f3cf, 2},
		{0x1f3d4, 1},
		{0x1f3e0, 2},
		{0x1f3f1, 1},
		{0x1f3f4, 2},
		{0x1f3f5, 1},
		{0x1f3f8, 2},
		{0x1f43f, 1},
		{0x1f440, 2},
		{0x1f441, 1},
		{0x1f442, 2},
		{0x1f4fd, 1},
		{0x1f4ff, 2},
		{0x1f53e, 1},
		{0x1f54b, 2},
		{0x1f54f, 1},
		{0x1f550, 2},
		{0x1f568, 1},
		{0x1f57a, 2},
		{0x1f57b, 1},
		{0x1f595, 2},
		{0x1f597, 1},
		{0x1f5a4, 2},
		{0x1f5a5, 1},
		{0x1f5fb, 2},
		{0x1f650, 1},
		{0x1f680, 2},
		{0x1f6c6, 1},
		{0x1f6cc, 2},
		{0x1f6cd, 1},
		{0x1f6d0, 2},
		{0x1f6d3, 1},
		{0x1f6eb, 2},
		{0x1f6ed, 1},
		{0x1f6f4, 2},
		{0x1f6fa, 1},
		{0x1f910, 2},
		{0x1f93f, 1},
		{0x1f940, 2},
		{0x1f971, 1},
		{0x1f973, 2},
		{0x1f977, 1},
		{0x1f97a, 2},
		{0x1f97b, 1},
		{0x1f97c, 2},
		{0x1f9a3, 1},
		{0x1f9b0, 2},
		{0x1f9ba, 1},
		{0x1f9c0, 2},
		{0x1f9c3, 1},
		{0x1f9d0, 2},
		{0x1fa00, 1},
		{0x20000, 2},
		{0x2fffe, 1},
		{0x30000, 2},
		{0x3fffe, 1},
		{0xe0001, 0},
		{0xe0002, 1},
		{0xe0020, 0},
		{0xe0080, 1},
		{0xe0100, 0},
		{0xe01f0, 1},
		{0xf0000, 2},
		{0xffffe, 1},
		{0x100000, 2},
		{0x10fffe, 1}
	};

    size_t getTTYWidth(char32_t cp){
		return (--std::upper_bound(ttyWidthDataList.begin(), ttyWidthDataList.end(), cp))->ttyWidth;
    }
    
}
}