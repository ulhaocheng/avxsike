/**
 *******************************************************************************
 * @version 0.1
 * @date 2021-12-16
 * @copyright Copyright © 2021 by University of Luxembourg
 * @author Hao Cheng
 *******************************************************************************
 */

#ifndef _SIDH_H
#define _SIDH_H

#include "curve.h"
#include "utils.h"
#include "random.h"

static const uint64_t vA_gen[6*VNWORDS] = {
  0x46F15019EC96A, 0x515D41CE2EE25, 0x019F20674A797, 0x212FF183EC81E,
  0x2D5E6D459F454, 0x7D8CC83A42BB3, 0x3020CB4A42AF8, 0x14826A5547FC2,
  0x5333CB2C45E13, 0x0CBAD9C692D27, 0x18BC60CC065D7, 0x09229EEF7FE0F, // XPA0
  0x32D3E4BA9CC3E, 0x17A69C9FDB602, 0x449721EFBA583, 0x5F9E7D51AA8DB,
  0x367D66A25D615, 0x50C0F8ED841B8, 0x1A027C8321B4E, 0x0DBDB1575D8B6,
  0x7915F6C637BA1, 0x67423C14DFF3F, 0x3EEC087D7DF0B, 0x12894A8D2D764, // XPA1
  0x25B91D7C945D3, 0x734BEF8259517, 0x3E1E616C072F8, 0x417ADE291A8F4,
  0x4A9FAA2D2CABF, 0x169FD5EC8E9D9, 0x1C8CD90076C69, 0x38D02FAE51CF9,
  0x7A6E89B90B79A, 0x5C4756377BE53, 0x17527F3C6B34C, 0x11103AB6E1876, // XQA0
  0x3C001E8B3AA23, 0x2519663C11528, 0x340899BA298F8, 0x3010A77B2FF02,
  0x018E22684A2D2, 0x4FA9E90A7B44A, 0x3CE2F006F57BA, 0x5A9C3F51D98E0,
  0x7B6FA76EF62D0, 0x415BEA22EA74D, 0x374E4D25FBF90, 0x0A273544BB684, // XQA1 
  0x0311261DD0782, 0x584B675CC9778, 0x06E2A2606C57F, 0x166AFFE22DCF9,
  0x6702C6AA3C0B5, 0x00A03C90CB402, 0x42DA89BCF3397, 0x3C1D80050FDC2,
  0x0FDA2B08EB251, 0x7D08F1D982952, 0x103987FDB52DD, 0x100DA56070079, // XRA0
  0x4873B980435A7, 0x056952FEE1C1F, 0x71FE937A5BD0F, 0x2B21F221FEA0A,
  0x451B354E5EED9, 0x428EE2C31B6AF, 0x62D273452D6D0, 0x376B822672193,
  0x19B0C0C031F15, 0x336D8CC73B304, 0x68A77E1AF2F33, 0x0997C134C0D58, // XRA1
};

static const uint64_t vB_gen[6*VNWORDS] = {
  0x2B95C6C8E180E, 0x442C3A5E9F786, 0x60C246F6CD024, 0x056A663F1C65F,
  0x314FBD7D742CC, 0x44D2AE2BF4FC3, 0x76BCFCA4F690F, 0x3E585950C3EEF,
  0x6F3849C24D2C9, 0x2569620719FC3, 0x4D5BAA583108F, 0x051661BBE9FC6, // XPB0
  0x0000000000000, 0x0000000000000, 0x0000000000000, 0x0000000000000, 
  0x0000000000000, 0x0000000000000, 0x0000000000000, 0x0000000000000, 
  0x0000000000000, 0x0000000000000, 0x0000000000000, 0x0000000000000, // XPB1
  0x65A9F586DB4A1, 0x6E25E21B2BCD8, 0x6AB0EE0D612E1, 0x4C0C164130CEA,
  0x08FD2304ECDAA, 0x7853BCFA982AB, 0x22EE464307677, 0x44C5C81E08043,
  0x783079D216AE3, 0x456E8AE478F27, 0x144CECA7DFB9C, 0x086002EDF542B, // XQB0
  0x0000000000000, 0x0000000000000, 0x0000000000000, 0x0000000000000, 
  0x0000000000000, 0x0000000000000, 0x0000000000000, 0x0000000000000, 
  0x0000000000000, 0x0000000000000, 0x0000000000000, 0x0000000000000, // XQB1
  0x3D767A87897A0, 0x07830F3D9A9A6, 0x70A28DBFEE868, 0x35153FE87DACA,
  0x30E56FAF53FF6, 0x1ABD2A9AB5224, 0x4C8DA664AE2D3, 0x5B9974AF466E6,
  0x58973E0CBC111, 0x4D5D7FE7CD830, 0x3B88ECECAE455, 0x0F467DD640F9F, // XRB0
  0x79235E3CC79B3, 0x3C06B153565D4, 0x4972D65460254, 0x3F8EE860C89DB,
  0x5AB9D19072463, 0x748BC508636CF, 0x595C619BCE9BF, 0x1BEAC67601FE9,
  0x302ADD7298A1E, 0x0D1E19769899A, 0x0AC966AA4BD8A, 0x08B267323EC8D, // XRB1
};

// Fixed parameters for isogeny tree computation
static const unsigned int strat_Alice[MAX_Alice-1] = { 
  67, 37, 21, 12, 7, 4, 2, 1, 1, 2, 1, 1, 3, 2, 1, 1, 1, 1, 5, 3, 2, 1, 1, 1, 1, 
  2, 1, 1, 1, 9, 5, 3, 2, 1, 1, 1, 1, 2, 1, 1, 1, 4, 2, 1, 1, 1, 2, 1, 1, 16, 9, 
  5, 3, 2, 1, 1, 1, 1, 2, 1, 1, 1, 4, 2, 1, 1, 1, 2, 1, 1, 8, 4, 2, 1, 1, 2, 1, 
  1, 4, 2, 1, 1, 2, 1, 1, 33, 16, 8, 5, 2, 1, 1, 1, 2, 1, 1, 1, 4, 2, 1, 1, 2, 1, 
  1, 8, 4, 2, 1, 1, 2, 1, 1, 4, 2, 1, 1, 2, 1, 1, 16, 8, 4, 2, 1, 1, 1, 2, 1, 1, 
  4, 2, 1, 1, 2, 1, 1, 8, 4, 2, 1, 1, 2, 1, 1, 4, 2, 1, 1, 2, 1, 1  };

static const unsigned int strat_Bob[MAX_Bob-1] = { 
  86, 48, 27, 15, 8, 4, 2, 1, 1, 2, 1, 1, 4, 2, 1, 1, 2, 1, 1, 7, 4, 2, 1, 1, 2, 1, 
  1, 3, 2, 1, 1, 1, 1, 12, 7, 4, 2, 1, 1, 2, 1, 1, 3, 2, 1, 1, 1, 1, 5, 3, 2, 1, 1, 
  1, 1, 2, 1, 1, 1, 21, 12, 7, 4, 2, 1, 1, 2, 1, 1, 3, 2, 1, 1, 1, 1, 5, 3, 2, 1, 1, 
  1, 1, 2, 1, 1, 1, 9, 5, 3, 2, 1, 1, 1, 1, 2, 1, 1, 1, 4, 2, 1, 1, 1, 2, 1, 1, 38, 
  21, 12, 7, 4, 2, 1, 1, 2, 1, 1, 3, 2, 1, 1, 1, 1, 5, 3, 2, 1, 1, 1, 1, 2, 1, 1, 1, 
  9, 5, 3, 2, 1, 1, 1, 1, 2, 1, 1, 1, 4, 2, 1, 1, 1, 2, 1, 1, 17, 9, 5, 3, 2, 1, 1, 
  1, 1, 2, 1, 1, 1, 4, 2, 1, 1, 1, 2, 1, 1, 8, 4, 2, 1, 1, 1, 2, 1, 1, 4, 2, 1, 1, 2, 
  1, 1 };
  
// 2^640 * 2^28 = 2^668 
static const uint64_t montRx2exp28[NWORDS_FIELD] = {
  0x0670CC8E66A81208, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
  0x6BF0000000000000, 0x3C9C60BF915E3D80, 0x541B0A71A1F6738D, 0x7343E6886C4F62B9, 
  0x2D436BE5982FAEC2, 0x00000000BA1D94D7, };

// 2^640 / 2^28 = 2^612
static const uint64_t montRdiv2exp28[NWORDS_FIELD] = {
  0x0000000000000006, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 
  0x6BF4000000000000, 0xD72E2C8C01DFDEE9, 0x5E918461E4A025F9, 0xD1FDCE239B672100, 
  0xF69F9B721490ECB3, 0x000000011838138C, };

void random_mod_order_B(unsigned char* random_digits);

void EphemeralKeyGeneration_A(const unsigned char* PrivateKeyA, unsigned char* PublicKeyA);
void EphemeralKeyGeneration_B(const unsigned char* PrivateKeyB, unsigned char* PublicKeyB);
void EphemeralSecretAgreement_A(const unsigned char* PrivateKeyA, const unsigned char* PublicKeyB, unsigned char* SharedSecretA);
void EphemeralSecretAgreement_B(const unsigned char* PrivateKeyB, const unsigned char* PublicKeyA, unsigned char* SharedSecretB);

void EphemeralKeyGenSecAgr_A_parallel(const unsigned char* PrivateKeyA, unsigned char* PublicKeyA, const unsigned char* PublicKeyB, unsigned char* SharedSecretA);

#endif

// p := 0x27BF6A768819010C251E7D88CB255B2FA10C4252A9AE7BF45048FF9ABB1784DE8AA5AB02E6E01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;

// XPA0 := 0x1B368BC6019B46CD802129209B3E65B98BC64A92BC4DB2F9F3AC96B97A1B9C124DF549B528F18BEECB1666D27D47530435E84221272F3A97FB80527D8F8A359F8F1598D365744CA3070A5F26C;
// XPA1 := 0x1459685DCA7112D1F6030DBC98F2C9CBB41617B6AD913E6523416CCBD8ED9C7841D97DF83092B9B3F2AF00D62E08DAD8FA743CBCCCC1782BE0186A3432D3C97C37CA16873BEDE01F0637C1AA2;
// XQA0 := 0x025DA39EC90CDFB9BC0F772CDA52CB8B5A9F478D7AF8DBBA0AEB3E52432822DD88C38F4E3AEC0746E56149F1FE89707C77F8BA4134568629724F4A8E34B06BFE5C5E66E0867EC38B283798B8A;
// XQA1 := 0x2250E1959256AE502428338CB4715399551AEC78D8935B2DC73FCDCFBDB1A0118A2D3EF03489BA6F637B1C7FEE7E5F31340A1A537B76B5B736B4CDD284918918E8C986FC02741FB8C98F0A0ED;
// XRA0 := 0x1B36A006D05F9E370D5078CCA54A16845B2BFF737C865368707C0DBBE9F5A62A9B9C79ADF11932A9FA4806210E25C92DB019CC146706DFBC7FA2638ECC4343C1E390426FAA7F2F07FDA163FB5;
// XRA1 := 0x183C9ABF2297CA69699357F58FED92553436BBEBA2C3600D89522E7009D19EA5D6C18CFF993AA3AA33923ED93592B0637ED0B33ADF12388AE912BC4AE4749E2DF3C3292994DCF37747518A992;

// XPB0 := 0x1587822E647707ED4313D3BE6A811A694FB201561111838A0816BFB5DEC625D23772DE48A26D78C04EEB26CA4A571C67CE4DC4C620282876B2F2FC2633CA548C3AB0C45CC991417A56F7FEFEB;
// XQB0 := 0x14E647CB19B7EAAAC640A9C26B9C26DB7DEDA8FC9399F4F8CE620D2B2200480F4338755AE16D0E090F15EA1882166836A478C6E161C938E4EB8C2DD779B45FFDD17DCDF158AF48DE126B3A047;
// XRB0 := 0x1DB73BC2DE666D24E59AF5E23B79251BA0D189629EF87E56C38778A448FACE312D08EDFB876C3FD45ECF3746D96E2CADBBA08B1A206C47DDD93137059E34C90E2E42E10F30F6E5F52DED74222;
// XRB1 := 0x1B2C30180DAF5D91871555CE8EFEC76A4D521F877B754311228C7180A3E2318B4E7A00341FF99F34E35BF7A1053CA76FD77C0AFAE38E2091862AB4F1DD4C8D9C83DE37ACBA6646EDB4C238B48;
