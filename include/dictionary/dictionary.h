#pragma once

#include <unordered_map>
#include <optional>
#include <vector>
#include <stdexcept>

namespace dictionary {

  /**
   * @brief 一个通用的字典类，支持键值对的存储和操作
   * @tparam Key 键的类型
   * @tparam Value 值的类型
   */
  template<typename Key, typename Value>
  class Dictionary {
    std::unordered_map<Key, Value> data;

  public:
    /**
     * @brief 默认构造函数
     */
    Dictionary() = default;

    /**
     * @brief 使用初始化列表构造字典
     * @param init 初始化列表
     */
    Dictionary(std::initializer_list<std::pair<const Key, Value>> init);

    /**
     * @brief 插入或更新键值对
     * @param key 键
     * @param value 值
     */
    void insert(const Key& key, const Value& value);

    /**
     * @brief 插入或更新键值对（移动语义）
     * @param key 键
     * @param value 值
     */
    void insert(const Key& key, Value&& value);

    /**
     * @brief 插入或更新键值对（移动语义，键和值）
     * @param key 键
     * @param value 值
     */
    void insert(Key&& key, Value&& value);

    /**
     * @brief 获取指定键对应的值
     * @param key 键
     * @return 如果键存在，返回对应的值；否则返回 std::nullopt
     */
    std::optional<Value> get(const Key& key) const;

    /**
     * @brief 检查字典中是否包含指定的键
     * @param key 键
     * @return 如果键存在返回 true，否则返回 false
     */
    bool contains(const Key& key) const;

    /**
     * @brief 删除指定键的键值对
     * @param key 键
     * @return 如果键存在并已删除返回 true，否则返回 false
     */
    bool remove(const Key& key);

    /**
     * @brief 清空字典
     */
    void clear();

    /**
     * @brief 获取字典中键值对的数量
     * @return 键值对的数量
     */
    size_t size() const;

    /**
     * @brief 检查字典是否为空
     * @return 如果字典为空返回 true，否则返回 false
     */
    bool empty() const;

    /**
     * @brief 获取所有键
     * @return 包含所有键的向量
     */
    std::vector<Key> keys() const;

    /**
     * @brief 获取所有值
     * @return 包含所有值的向量
     */
    std::vector<Value> values() const;

    /**
     * @brief 使用 [] 运算符访问或插入值
     * @param key 键
     * @return 值的引用
     */
    Value& operator[](const Key& key);

    /**
     * @brief 使用 [] 运算符访问值（只读）
     * @param key 键
     * @return 值的引用
     */
    const Value& operator[](const Key& key) const;

    /**
     * @brief 检查两个字典是否相等
     * @param other 另一个字典
     * @return 如果相等返回 true，否则返回 false
     */
    bool operator==(const Dictionary<Key, Value>& other) const;

    /**
     * @brief 检查两个字典是否不相等
     * @param other 另一个字典
     * @return 如果不相等返回 true，否则返回 false
     */
    bool operator!=(const Dictionary<Key, Value>& other) const;
  };

  // 实现

  template<typename Key, typename Value>
  Dictionary<Key, Value>::Dictionary(std::initializer_list<std::pair<const Key, Value>> init)
      : data(init) {
  }

  template<typename Key, typename Value>
  void Dictionary<Key, Value>::insert(const Key& key, const Value& value) {
    data[key] = value;
  }

  template<typename Key, typename Value>
  void Dictionary<Key, Value>::insert(const Key& key, Value&& value) {
    data[key] = std::move(value);
  }

  template<typename Key, typename Value>
  void Dictionary<Key, Value>::insert(Key&& key, Value&& value) {
    data[std::move(key)] = std::move(value);
  }

  template<typename Key, typename Value>
  std::optional<Value> Dictionary<Key, Value>::get(const Key& key) const {
    auto it = data.find(key);
    if (it != data.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  template<typename Key, typename Value>
  bool Dictionary<Key, Value>::contains(const Key& key) const {
    return data.find(key) != data.end();
  }

  template<typename Key, typename Value>
  bool Dictionary<Key, Value>::remove(const Key& key) {
    return data.erase(key) > 0;
  }

  template<typename Key, typename Value>
  void Dictionary<Key, Value>::clear() {
    data.clear();
  }

  template<typename Key, typename Value>
  size_t Dictionary<Key, Value>::size() const {
    return data.size();
  }

  template<typename Key, typename Value>
  bool Dictionary<Key, Value>::empty() const {
    return data.empty();
  }

  template<typename Key, typename Value>
  std::vector<Key> Dictionary<Key, Value>::keys() const {
    std::vector<Key> result;
    result.reserve(data.size());
    for (const auto& pair : data) {
      result.push_back(pair.first);
    }
    return result;
  }

  template<typename Key, typename Value>
  std::vector<Value> Dictionary<Key, Value>::values() const {
    std::vector<Value> result;
    result.reserve(data.size());
    for (const auto& pair : data) {
      result.push_back(pair.second);
    }
    return result;
  }

  template<typename Key, typename Value>
  Value& Dictionary<Key, Value>::operator[](const Key& key) {
    return data[key];
  }

  template<typename Key, typename Value>
  const Value& Dictionary<Key, Value>::operator[](const Key& key) const {
    auto it = data.find(key);
    if (it != data.end()) {
      return it->second;
    }
    // 对于const版本，如果键不存在，抛出异常
    throw std::out_of_range("Key not found in dictionary");
  }

  template<typename Key, typename Value>
  bool Dictionary<Key, Value>::operator==(const Dictionary<Key, Value>& other) const {
    return data == other.data;
  }

  template<typename Key, typename Value>
  bool Dictionary<Key, Value>::operator!=(const Dictionary<Key, Value>& other) const {
    return !(*this == other);
  }

}  // namespace dictionary
