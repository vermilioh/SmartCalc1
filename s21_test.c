#include <check.h>
#include <stdlib.h>

#include "s21_smart_calc.h"

START_TEST(s21_parserTest) {  // parser and calc
  // simple operations:
  char data1[256] = "25+10/2+3/7";
  char data2[256] = "2*10-10/2+6/2-2";
  char data3[256] = "2+5-2";
  char data4[256] = "59-15*4+2";
  char data5[256] = "2*10-4/2+6/2-2";
  char data6[256] = "25+10/2+10/2";
  char data7[256] = "1-2";
  char data8[256] = "1-2-5-6-9/2";
  char data9[256] = "25/2/4/6/1";
  char data10[256] = "25+(10-2)+10/2";
  char data666[256] = "2-2*2-10*12";
  char data665[256] = "2-2/2-10*12";
  char data664[256] = "-10+5";
  ck_assert_float_eq(s21_parser(data1), 30.4285714285714286);
  ck_assert_float_eq(s21_parser(data2), 16);
  ck_assert_float_eq(s21_parser(data3), 5);
  ck_assert_float_eq(s21_parser(data4), 1);
  ck_assert_float_eq(s21_parser(data5), 19);
  ck_assert_float_eq(s21_parser(data6), 35);
  ck_assert_float_eq(s21_parser(data7), -1);
  ck_assert_float_eq(s21_parser(data8), -16.5);
  ck_assert_float_eq(s21_parser(data9), 0.5208333333333333);
  ck_assert_float_eq(s21_parser(data10), 38);
  ck_assert_float_eq(s21_parser(data666), -122);
  ck_assert_float_eq(s21_parser(data665), -119);
  ck_assert_float_eq(s21_parser(data664), -5);

  // brackets:
  char data11[256] = "1+2*(3+4/2-(1+2))*2+1";
  char data12[256] = "1+2*(3+18/2-(1+2)*3)*2+1";
  char data13[256] = "(1+2)*(3+18/2-(1+2)*3)*2+1";
  char data14[256] = "(1+2)*(3+18/2-(1+2)*3)*(2+1)";
  char data998[256] = "1+((2))";
  ck_assert_float_eq(s21_parser(data11), 10);
  ck_assert_float_eq(s21_parser(data12), 14);
  ck_assert_float_eq(s21_parser(data13), 19);
  ck_assert_float_eq(s21_parser(data14), 27);
  ck_assert_float_eq(s21_parser(data998), 3);

  // mod:
  char data15[256] = "50mod24";
  char data16[256] = "50mod5";
  char data17[256] = "25+50mod24";
  char data18[256] = "(25+34)-50mod24";
  char data999[256] = "25+2mod(2+3)";
  ck_assert_float_eq(s21_parser(data15), 2);
  ck_assert_float_eq(s21_parser(data16), 0);
  ck_assert_float_eq(s21_parser(data17), 27);
  ck_assert_float_eq(s21_parser(data18), 57);
  ck_assert_float_eq(s21_parser(data999), 27);

  // trigonometry:
  char data19[256] = "25+cos(3)-6*5";
  char data20[256] = "(25+cos(3))-6*5";
  char data21[256] = "(25+cos(3)-6)*5";
  char data22[256] = "cos(45)";
  char data23[256] = "cos(3)";
  char data24[256] = "log(25)";
  char data25[256] = "log(25)+cos(3)";
  char data26[256] = "sin(-7)";
  char data27[256] = "sin(-7)+256";
  char data28[256] = "2-(2*2)-sin(-10)+log(3)*12";
  char data29[256] = "2-2*2-sin(-10)+log(3)";
  char data30[256] = "log(3)*2";
  char data31[256] = "25*log(3)*2";
  char data32[256] = "25-log(3)*2";
  char data33[256] = "log(25.5)";
  char data111[256] = "tan(10)+acos(0.1)-asin(0.56)+atan(0.5)";
  char data112[256] = "sqrt(25)+ln(5)";

  ck_assert_float_eq(s21_parser(data19), -5.9899924966);
  ck_assert_float_eq(s21_parser(data20), -5.9899924966);
  ck_assert_float_eq(s21_parser(data21), 90.050037517);
  ck_assert_float_eq(s21_parser(data22), 0.52532198881);
  ck_assert_float_eq(s21_parser(data23), -0.9899924966);
  ck_assert_float_eq(s21_parser(data24), 1.39794000867);
  ck_assert_float_eq(s21_parser(data25), 0.40794751207);
  ck_assert_float_eq(s21_parser(data26), -0.65698659871);
  ck_assert_float_eq(s21_parser(data27), 255.343013401);
  ck_assert_float_eq(s21_parser(data28), 3.18143394575);
  ck_assert_float_eq(s21_parser(data29), -2.06689985617);
  ck_assert_float_eq(s21_parser(data30), 0.95424250943);
  ck_assert_float_eq(s21_parser(data31), 23.856062736);
  ck_assert_float_eq(s21_parser(data32), 24.0457574906);
  ck_assert_float_eq(s21_parser(data33), 1.40654018043);
  ck_assert_float_eq(s21_parser(data111), 1.9882515420921675897);
  ck_assert_float_eq(s21_parser(data112), 6.6094379124341005038);
  // unary:
  char data34[256] = "24+-3";
  char data35[256] = "-10+9";

  ck_assert_float_eq(s21_parser(data34), 21);
  ck_assert_float_eq(s21_parser(data35), -1);

  // pow:
  char data36[256] = "2^2";
  char data37[256] = "2^3";
  char data38[256] = "10^5";
  char data39[256] = "(2^(5^2))";

  ck_assert_float_eq(s21_parser(data36), 4);
  ck_assert_float_eq(s21_parser(data37), 8);
  ck_assert_float_eq(s21_parser(data38), 100000);
  ck_assert_float_eq(s21_parser(data39), 33554432);

  // general:
  char data45[256] = "-2*(3+sin(-10))*3";
  char data46[256] = "-233*42-74/4.3-0.987+24*(1+3)/-2";
  char data47[256] = "4^2-25mod25-123.43+4*(154-0.23)-cos(11-34*23)+32mod32";
  char data48[256] = "(123.43+4)-32-12mod11";
  char data49[256] = "-233*42-74/4.3-cos(0.987)+24*(1+3)/-2*sin(5-2)";
  char data50[256] = "-cos(0.987)";
  char data51[256] = "atan(424)-sqrt(5)";

  char data52[256] = "acos(0.5)+asin(0.5)+ln(5)+log(5)*tan(10)";
  char data53[256] = "2+(-2)";
  char data54[256] = "sin(25-2)";
  char data55[256] = "25-(-26)";
  char data56[256] = "sin(cos(2))";
  char data57[256] = "-cos(1)+25";
  ck_assert_float_eq(s21_parser(data45), -21.2641266653);
  ck_assert_float_eq(s21_parser(data46), -9852.19630233);
  ck_assert_float_eq(s21_parser(data47), 507.908043389);
  ck_assert_float_eq(s21_parser(data48), 94.43);
  ck_assert_float_eq(s21_parser(data49), -9810.53425818);
  ck_assert_float_eq(s21_parser(data50), -0.55119546565);  // fail
  ck_assert_float_eq(s21_parser(data57), 24.4596976941);

  char converted_res1[256];
  gcvt(s21_parser(data51), 7, converted_res1);
  char res1[11] = "-0.6676301";
  ck_assert_str_eq(converted_res1, res1);

  ck_assert_float_eq(s21_parser(data52), 3.6334190);
  ck_assert_float_eq(s21_parser(data53), 0);
  ck_assert_float_eq(s21_parser(data54), -0.84622040417);

  ck_assert_float_eq(s21_parser(data55), 51);
  ck_assert_float_eq(s21_parser(data56), -0.40423915385);
}
END_TEST

START_TEST(s21_init_parserTest) {       // init parser
  char data1[256] = "cos(45)+cos(45)";  // 1
  s21_init_parser(data1);
  ck_assert_str_eq(data1, "a(45)+a(45)");

  char data2[256] = "sin(45)+sin(45)";  // 2
  s21_init_parser(data2);
  ck_assert_str_eq(data2, "b(45)+b(45)");

  char data3[256] = "sin(45)";  // 3
  s21_init_parser(data3);
  ck_assert_str_eq(data3, "b(45)");

  char data4[256] = "log(25)";  // 4
  s21_init_parser(data4);
  ck_assert_str_eq(data4, "k(25)");

  char data5[256] = "sin(45)+log(28)";  // 5
  s21_init_parser(data5);
  ck_assert_str_eq(data5, "b(45)+k(28)");

  char data6[256] = "39+sin(45)+82-log(28)*7";  // 6
  s21_init_parser(data6);
  ck_assert_str_eq(data6, "39+b(45)+82-k(28)*7");

  char data7[256] = "(39+sin(45))+82-(log(28)*7)";  // 7
  s21_init_parser(data7);
  ck_assert_str_eq(data7, "(39+b(45))+82-(k(28)*7)");

  char data8[256] = "sin(-8)";  // 8 minus
  s21_init_parser(data8);
  ck_assert_str_eq(data8, "b(-8)");

  char data9[256] = "sin(-81)";  // 9 minus
  s21_init_parser(data9);
  ck_assert_str_eq(data9, "b(-81)");

  char data10[256] = "50mod24";
  s21_init_parser(data10);
  ck_assert_str_eq(data10, "50m24");
}
END_TEST

START_TEST(s21_validationTest) {  // validation
  int succes = 0;
  int fail = 1;

  // sign in the beggining of str:
  char data1[256] = "+2-5";
  char data2[256] = "*2-5";
  char data599[256] = "-2-5";
  ck_assert_int_eq(s21_validation(data1), succes);
  ck_assert_int_eq(s21_validation(data2), fail);
  ck_assert_int_eq(s21_validation(data599), succes);

  // sign in the end of str:
  char data3[256] = "2-5+";
  char data4[256] = "2-5*";
  ck_assert_int_eq(s21_validation(data3), fail);
  ck_assert_int_eq(s21_validation(data4), fail);

  // brackets:
  char data5[256] = "(25+2)+(2-5)";
  char data6[256] = "(25+2)+(2-5))";
  ck_assert_int_eq(s21_validation(data5), succes);
  ck_assert_int_eq(s21_validation(data6), fail);

  // spaces:
  char data7[256] = "26+ 7";
  char data8[256] = "26+7 ";
  ck_assert_int_eq(s21_validation(data7), fail);
  ck_assert_int_eq(s21_validation(data8), fail);

  // inside brackets:
  char data9[256] = "2+(2-)";
  char data10[256] = "2+(-2)";
  char data99[256] = "1+((2))";
  char data100[256] = "(10+(25+6))";
  char data101[256] = "(10(25+6))";

  ck_assert_int_eq(s21_validation(data9), fail);
  ck_assert_int_eq(s21_validation(data10), succes);
  ck_assert_int_eq(s21_validation(data99), succes);
  ck_assert_int_eq(s21_validation(data100), succes);
  ck_assert_int_eq(s21_validation(data101), fail);

  // between brackets:
  char data11[256] = "(15-5)mod(5^3)";
  char data12[256] = "(15-5)+(5^3)";
  char data13[256] = "25+2mod(2+3)";

  ck_assert_int_eq(s21_validation(data11), fail);
  ck_assert_int_eq(s21_validation(data12), succes);
  ck_assert_int_eq(s21_validation(data13), succes);

  // after bracket ')':
  char data14[256] = "(3+5)sin(8)";
  char data15[256] = "(3+5)+sin(8)";
  char data16[256] = "(3+5)25(8)";
  ck_assert_int_eq(s21_validation(data14), fail);
  ck_assert_int_eq(s21_validation(data15), succes);
  ck_assert_int_eq(s21_validation(data16), fail);

  // dots in double:
  char data17[256] = "2.25+2..4";
  char data18[256] = "45.4+4.*2";
  char data19[256] = "45.4+4.2";
  ck_assert_int_eq(s21_validation(data17), fail);
  ck_assert_int_eq(s21_validation(data18), fail);
  ck_assert_int_eq(s21_validation(data19), succes);

  // trigonometry:
  char data20[256] = "30sin(8)";
  char data21[256] = "30+sin(8)";
  char data22[256] = "sin()";
  char data23[256] = "sin(25+2";
  char data24[256] = "sin";
  char data25[256] = "25-cos(5)";
  char data26[256] = "sin(25)-cos(25)";
  char data27[256] = "sin(9";
  char data28[256] = "sin(9)";
  char data29[256] = "sqrt(9)+log(23)-ln(10)+atan(0.45)";
  char data30[256] = "sin(cos(5))";

  ck_assert_int_eq(s21_validation(data20), fail);
  ck_assert_int_eq(s21_validation(data21), succes);
  ck_assert_int_eq(s21_validation(data22), fail);
  ck_assert_int_eq(s21_validation(data23), fail);
  ck_assert_int_eq(s21_validation(data24), fail);
  ck_assert_int_eq(s21_validation(data25), succes);
  ck_assert_int_eq(s21_validation(data26), succes);
  ck_assert_int_eq(s21_validation(data27), fail);
  ck_assert_int_eq(s21_validation(data28), succes);
  ck_assert_int_eq(s21_validation(data29), succes);
  ck_assert_int_eq(s21_validation(data30), succes);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_parserTest);       // 1
  tcase_add_test(tc1_1, s21_init_parserTest);  // 2
  tcase_add_test(tc1_1, s21_validationTest);   // 3
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
