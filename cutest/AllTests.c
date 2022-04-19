
#include <stdio.h>
#include "CuTest.h"
#include "AllTests.h"
#include "../serialization.h"

void testSerialization(CuTest *tc)
{
  serialized_buffer_t *s_buffer = init_buffer();

  CuAssertPtrNotNullMsg(tc, "Buffer's pointer must not be null!", s_buffer);
  CuAssertIntEquals_Msg(tc, "Buffer size must be equal to 512 (default value)", 512, s_buffer->size);

  int number = 42;
  char *test_string = "test de chaîne de caractères è_àoàà'çàçç_éçàéà&)5434565877899076875674563 !";

  serialize_data(s_buffer, &number, sizeof(int));
  serialize_data(s_buffer, test_string, strlen(test_string) + 1);

  CuAssertIntEquals_Msg(tc, "Seek index value is not correct!", sizeof(int) + strlen(test_string) + 1, s_buffer->seek_index);

  // Don't forget to reset seek index before unserialize
  reset_seek(s_buffer);

  CuAssertIntEquals_Msg(tc, "Seek value index must be equal to zero", 0, s_buffer->seek_index);

  int number_unserial = 0;
  char *string_test = (char *)malloc(strlen(test_string) + 1);

  unserialize_data(&number_unserial, s_buffer, sizeof(int));
  unserialize_data(string_test, s_buffer, strlen(test_string) + 1);

  CuAssertStrEquals_Msg(tc, "String mismatch!", test_string, string_test);
  CuAssertIntEquals_Msg(tc, "Number mismatch!", number, number_unserial);

  free_buffer(s_buffer);

  s_buffer = init_buffer_size(sizeof(int));

  CuAssertPtrNotNullMsg(tc, "Buffer's pointer must not be null!", s_buffer);
  CuAssertIntEquals_Msg(tc, "Buffer's size must be equal to size of int", sizeof(int), s_buffer->size);

  number = 10;
  int actual_number = 31;

  serialize_data(s_buffer, &number, sizeof(int));

  CuAssertIntEquals_Msg(tc, "Seek index value is not correct", sizeof(int), s_buffer->seek_index);

  serialize_data(s_buffer, &actual_number, sizeof(int));

  CuAssertIntEquals_Msg(tc, "Buffer's size is not correct", sizeof(int) * 2, s_buffer->size);
  CuAssertIntEquals_Msg(tc, "Seek index value is not correct", sizeof(int) * 2, s_buffer->seek_index);

  // Don't forget to reset seek index before unserialize
  reset_seek(s_buffer);

  CuAssertIntEquals_Msg(tc, "Seek value index must be equal to zero", 0, s_buffer->seek_index);

  number_unserial = 0;
  int number_expected = 0;

  unserialize_data(&number_unserial, s_buffer, sizeof(int));
  unserialize_data(&number_expected, s_buffer, sizeof(int));

  CuAssertIntEquals_Msg(tc, "Number 1 mismatch!", number, number_unserial);
  CuAssertIntEquals_Msg(tc, "Number 2 mismatch!", actual_number, number_expected);

  free_buffer(s_buffer);
}

CuSuite *SuiteTest()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, testSerialization);
  return suite;
}

void RunAllTests(void)
{
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  CuSuiteAddSuite(suite, SuiteTest());

  CuSuiteRun(suite);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);
}

int main(int argc, char *argv[])
{
  RunAllTests();
  return 0;
}