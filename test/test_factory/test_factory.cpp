#include <Factory.h>
#include <unity.h>

void test_FactoryNotKnown() {
  String                                 msg = "AB1CDE-10>APRS:AABCDE";
  std::shared_ptr<aprs::NotKnownMessage> pos = std::static_pointer_cast<aprs::NotKnownMessage>(aprs::Factory::generate(msg));
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", pos->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", pos->getDestination().c_str());
  TEST_ASSERT_EQUAL_STRING("ABCDE", pos->getText().c_str());
}

void test_FactoryPositionIn1() {
  String                          msg = "AB1CDE-10>APRS:=1234.12N/12345.12E-QTH von AB1CDE";
  std::shared_ptr<aprs::Position> pos = std::static_pointer_cast<aprs::Position>(aprs::Factory::generate(msg));
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", pos->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", pos->getDestination().c_str());
  TEST_ASSERT_EQUAL_DOUBLE(12.56866666666666666667, pos->getLatitude());
  TEST_ASSERT_EQUAL_DOUBLE(123.752, pos->getLongitude());
  TEST_ASSERT_EQUAL_STRING("QTH von AB1CDE", pos->getText().c_str());
}

void test_FactoryPositionIn2() {
  String                          msg = "AB1CDE-10>APRS,AB1CDE:=1234.12N/12345.12E-QTH von AB1CDE";
  std::shared_ptr<aprs::Position> pos = std::static_pointer_cast<aprs::Position>(aprs::Factory::generate(msg));
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", pos->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", pos->getDestination().c_str());
  for (auto &path : pos->getPath().get()) {
    TEST_ASSERT_EQUAL_STRING("AB1CDE", path->getName().c_str());
  }
  TEST_ASSERT_EQUAL_DOUBLE(12.56866666666666666667, pos->getLatitude());
  TEST_ASSERT_EQUAL_DOUBLE(123.752, pos->getLongitude());
  TEST_ASSERT_EQUAL_STRING("QTH von AB1CDE", pos->getText().c_str());
}

#ifdef NATIVE
int main(int argc, char **argv)
#else
void setup()
#endif
{
  UNITY_BEGIN();
  RUN_TEST(test_FactoryNotKnown);
  RUN_TEST(test_FactoryPositionIn1);
  RUN_TEST(test_FactoryPositionIn2);
  UNITY_END();
}

void loop() {
}