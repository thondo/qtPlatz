
#include <iostream>
#include <libs/adprocessor/peakd.hpp>

extern std::vector< std::tuple< double, double, double, double, double > > __data;

int
main()
{
    constexpr int ndim = 4;
    constexpr int nprod = 2;

    Eigen::Matrix<double, ndim, nprod> A;

    A <<                  /* PGE2 */   /* PGD2 */
        /*233.2 */        0.1215,       0.4336
        /*271.2 */        , 1.0000,     1.0000
        /*315.2 */        , 0.9099,     0.8303
        /*333.2 */        , 0.7210,     0.2837
        ;

    std::cout << "A=" << A << std::endl;

    auto peakd = adprocessor::PeakDecomposition< double, 4, 2 >( A );

    for ( const auto& data: __data ) {
        auto [b,v] = peakd( std::get<1>( data ), std::get<2>( data ), std::get<3>( data ), std::get<4>( data )  );
        std::cout << "Time=" << std::get< 0 >(data) << std::endl
                  << "b=" << b << std::endl << "---------------------" << std::endl
                  << "v=" << v(0) << ", " << v(1) << std::endl << "---------------------" << std::endl;
    }

}

std::vector< std::tuple< double, double, double, double, double > > __data = {
    {60.288,	133,	472,	217,	-89},
    {60.656,	117,	483,	272,	67},
    {61.024,	67,	550,	389,	367},
    {61.392,	122,	817,	656,	672},
    {61.76,	394,	2428,	1911,	1706},
    {62.128,	1006,	6764,	5713,	4702},
    {62.496,	1789,	14653,	12601,	10850},
    {62.864,	2711,	25509,	22366,	19374},
    {63.232,	3756,	36475,	31911,	27704},
    {63.6,	4740,	44878,	39700,	33205},
    {63.968,	5524,	48094,	43194,	35091},
    {64.336,	5768,	47482,	43205,	34234},
    {64.704,	5723,	44208,	40083,	31642},
    {65.072,	5240,	40551,	35592,	28209},
    {65.44,	4556,	36632,	31146,	24465},
    {65.808,	4062,	33966,	28498,	21684},
    {66.176,	5312,	33048,	28414,	19888},
    {66.544,	9092,	36205,	32053,	19799},
    {66.912,	15558,	44268,	39151,	20700},
    {67.28,	22676,	56365,	49050,	22441},
    {67.648,	28865,	67829,	58054,	23325},
    {68.016,	32370,	74832,	62894,	23169},
    {68.384,	33187,	76537,	63551,	21712},
    {68.752,	31869,	74218,	61044,	20138},
    {69.12,	29482,	69330,	57272,	18431},
    {69.488,	26817,	62789,	52098,	17214},
    {69.856,	24248,	56554,	46363,	16007},
    {70.224,	21762,	51474,	41330,	14723},
    {70.592,	19448,	47354,	36622,	13066},
    {70.96,	16841,	43011,	32560,	11409},
    {71.328,	14433,	38208,	28053,	10248},
    {71.696,	12293,	33544,	24443,	9558},
    {72.064,	11098,	29532,	21851,	9163},
    {72.432,	10331,	26005,	20394,	8658},
    {72.8,	9669,	23107,	19132,	8018},
    {73.168,	8758,	20616,	17486,	7196},
    {73.536,	7780,	19020,	15868,	6551},
    {73.904,	6868,	18025,	14444,	6162},
    {74.272,	6140,	17391,	13488,	5846},
    {74.64,	5784,	16701,	12660,	5368}
};