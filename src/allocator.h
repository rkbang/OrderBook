#pragma once
#include <stack>
#include <memory>

namespace order_book
{
  constexpr uint32_t max_allocated_size = 1000;
  template <class T>
  class Allocator : public std::allocator<T>
  {
  public:
    ~Allocator()
    {
      while (!object_stack_.empty())
      {
        std::allocator<T>::deallocate(GetTop(), sizeof(T));
      }
    }

    void deallocate(T *obj)
    {
      if (object_stack_.size() < max_allocated_size)
      {
        object_stack_.push(obj);
      }
      else
      {
        std::allocator<T>::deallocate(obj, sizeof(T));
      }
    }

    std::shared_ptr<T> allocate()
    {
      T *obj_ptr;
      if (object_stack_.empty())
      {
        obj_ptr = std::allocator<T>::allocate(sizeof(T), nullptr);
      }
      else
      {
        obj_ptr = GetTop();
      }

      return std::shared_ptr<T>(obj_ptr, [this](T *ptr) { deallocate(ptr); });
    }

  private:
    T *GetTop()
    {
      T *obj = object_stack_.top();
      object_stack_.pop();
      return obj;
    }

    std::stack<T *> object_stack_;
  };
}