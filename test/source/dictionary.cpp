#include <doctest/doctest.h>
#include <dictionary/dictionary.h>

#include <algorithm>
#include <string>

TEST_CASE("Dictionary - 基本操作") {
  using namespace dictionary;

  Dictionary<std::string, int> dict;

  // 测试空字典
  CHECK(dict.empty());
  CHECK(dict.size() == 0);

  // 测试插入
  dict.insert("one", 1);
  dict.insert("two", 2);
  dict.insert("three", 3);

  CHECK(dict.size() == 3);
  CHECK_FALSE(dict.empty());

  // 测试包含
  CHECK(dict.contains("one"));
  CHECK(dict.contains("two"));
  CHECK_FALSE(dict.contains("four"));

  // 测试获取
  auto value1 = dict.get("one");
  CHECK(value1.has_value());
  CHECK(value1.value() == 1);

  auto value4 = dict.get("four");
  CHECK_FALSE(value4.has_value());

  // 测试 [] 运算符
  CHECK(dict["one"] == 1);
  CHECK(dict["two"] == 2);
  dict["four"] = 4;
  CHECK(dict["four"] == 4);
  CHECK(dict.size() == 4);

  // 测试删除
  CHECK(dict.remove("one"));
  CHECK_FALSE(dict.contains("one"));
  CHECK(dict.size() == 3);
  CHECK_FALSE(dict.remove("nonexistent"));

  // 测试清空
  dict.clear();
  CHECK(dict.empty());
  CHECK(dict.size() == 0);
}

TEST_CASE("Dictionary - 初始化列表") {
  using namespace dictionary;

  Dictionary<std::string, int> dict{{"a", 1}, {"b", 2}, {"c", 3}};

  CHECK(dict.size() == 3);
  CHECK(dict["a"] == 1);
  CHECK(dict["b"] == 2);
  CHECK(dict["c"] == 3);
}

TEST_CASE("Dictionary - 移动语义") {
  using namespace dictionary;

  Dictionary<std::string, std::string> dict;

  std::string key = "test_key";
  std::string value = "test_value";

  dict.insert(std::move(key), std::move(value));

  CHECK(dict.contains("test_key"));
  CHECK(dict["test_key"] == "test_value");
}

TEST_CASE("Dictionary - 键和值列表") {
  using namespace dictionary;

  Dictionary<std::string, int> dict;
  dict.insert("a", 1);
  dict.insert("b", 2);
  dict.insert("c", 3);

  auto keys = dict.keys();
  auto values = dict.values();

  CHECK(keys.size() == 3);
  CHECK(values.size() == 3);

  // 检查键是否包含预期的值
  CHECK(std::find(keys.begin(), keys.end(), "a") != keys.end());
  CHECK(std::find(keys.begin(), keys.end(), "b") != keys.end());
  CHECK(std::find(keys.begin(), keys.end(), "c") != keys.end());

  // 检查值是否包含预期的值
  CHECK(std::find(values.begin(), values.end(), 1) != values.end());
  CHECK(std::find(values.begin(), values.end(), 2) != values.end());
  CHECK(std::find(values.begin(), values.end(), 3) != values.end());
}

TEST_CASE("Dictionary - 相等性比较") {
  using namespace dictionary;

  Dictionary<std::string, int> dict1;
  dict1.insert("a", 1);
  dict1.insert("b", 2);

  Dictionary<std::string, int> dict2;
  dict2.insert("a", 1);
  dict2.insert("b", 2);

  Dictionary<std::string, int> dict3;
  dict3.insert("a", 1);
  dict3.insert("b", 3);

  CHECK(dict1 == dict2);
  CHECK_FALSE(dict1 == dict3);
  CHECK(dict1 != dict3);
}

TEST_CASE("Dictionary - 不同类型的键值对") {
  using namespace dictionary;

  // 测试整数键和字符串值
  Dictionary<int, std::string> dict1;
  dict1.insert(1, "one");
  dict1.insert(2, "two");
  CHECK(dict1[1] == "one");
  CHECK(dict1[2] == "two");

  // 测试字符串键和字符串值
  Dictionary<std::string, std::string> dict2;
  dict2.insert("name", "John");
  dict2.insert("age", "30");
  CHECK(dict2["name"] == "John");
}

TEST_CASE("Dictionary - 更新值") {
  using namespace dictionary;

  Dictionary<std::string, int> dict;
  dict.insert("key", 1);
  CHECK(dict["key"] == 1);

  // 更新值
  dict.insert("key", 2);
  CHECK(dict["key"] == 2);
  CHECK(dict.size() == 1);

  // 使用 [] 运算符更新
  dict["key"] = 3;
  CHECK(dict["key"] == 3);
}
