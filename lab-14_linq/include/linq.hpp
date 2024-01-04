#ifndef LINQ_HPP_
#define LINQ_HPP_

#include <utility>
#include <vector>
#include <iterator>

namespace linq {

    namespace impl {

        template<typename T, typename Iter>
        class range_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T, typename U, typename F>
        class select_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T>
        class take_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        template<typename T>
        class enumerator {
        public:
          virtual const T &operator*() = 0;
          virtual enumerator &operator++() = 0;
          virtual explicit operator bool() const = 0;

          auto drop(int count) {
              return drop_enumerator<T>(*this, count);
          }

          template<typename U = T, typename F>
          auto select(F func) {
              return select_enumerator<U, T, F>(*this, std::move(func));
          }

          template<typename F>
          auto until(F func) {
              return until_enumerator<T, F>(*this, std::move(func));
          }

          auto take(int count) {
              return take_enumerator<T>(*this, count);
          }

          template<typename F>
          auto where(F func) {
              return where_enumerator<T, F>(*this, std::move(func));
          }

          auto where_neq(T t) {
              return where([t](T cur) { return cur != t; });
          }

          auto until_eq(T t) {
              return until([t](T cur) { return cur == t; });
          }

          std::vector<T> to_vector() {
              std::vector <T> res;
              while (*this) {
                  res.push_back(**this);
                  ++(*this);
              }
              return res;
          }

          template<typename Iter>
          void copy_to(Iter it) {
              while (*this) {
                  *it = **this;
                  it++;
                  ++(*this);
              }
          }
        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
          range_enumerator(Iter begin, Iter end) : _begin(begin), _end(end) {}

          virtual explicit operator bool() const {
              return _begin != _end;
          }

          virtual enumerator<T> &operator++() {
              ++_begin;
              return *this;
          }

          virtual const T &operator*() {
              return *_begin;
          }
        private:
          Iter _begin, _end;
        };

        template<typename T>
        class drop_enumerator : public enumerator<T> {
        public:
          drop_enumerator(enumerator<T> &parent, int count) : _parent(parent), _count(count) {
              while ((bool) _parent && _count > 0) {
                  ++_parent;
                  --_count;
              }
          }

          virtual explicit operator bool() const {
              return (bool) _parent;
          }

          virtual enumerator<T> &operator++() {
              ++_parent;
              return *this;
          }

          virtual const T &operator*() {
              return *_parent;
          }

        private:
            enumerator<T> &_parent;
            int _count;
        };

        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<T> {
        public:
          select_enumerator(enumerator<U> &parent, F func) : _parent(parent), _func(std::move(func)) {
              if((bool) _parent)
                _item = _func(*_parent);
          }

          virtual explicit operator bool() const {
              return (bool) _parent;
          }

          virtual enumerator<T> &operator++() {
              ++_parent;
              if ((bool)_parent)
                _item = _func(*_parent);
              return *this;
            }

          virtual const T &operator*() {
              return _item;
          }

        private:
            enumerator<U> &_parent;
            F _func;
            T _item;
        };

        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
          until_enumerator(enumerator<T> &parent, F predicate) : _parent(parent), _predicate(std::move(predicate)) {}

          virtual explicit operator bool() const {
              return (bool) _parent && !_predicate(*_parent);
          }

          virtual enumerator<T> &operator++() {
              if ((bool) _parent && !_predicate(*_parent))
                  ++_parent;
              return *this;
          }

          virtual const T &operator*() {
              return *_parent;
          }
        private:
            enumerator<T> &_parent;
            F _predicate;
        };

        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int count) : _parent(parent), _count(count) {}

            virtual operator bool() const {
                return _count > 0 && (bool) _parent;
            }

            virtual enumerator<T> &operator++() {
                --_count;
                if (_count > 0)
                    ++_parent;
                return *this;
            }

            virtual const T &operator*() {
                return *_parent;
            }

        private:
            enumerator<T> &_parent;
            int _count;
        };

        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F func) : _parent(parent), _func(std::move(func)) {
                while ((bool) _parent && !_func(*_parent))
                    ++_parent;
            }

            virtual operator bool() const {
                return (bool) _parent;
            }

            virtual enumerator<T> &operator++() {
                ++_parent;
                while ((bool) _parent && !_func(*_parent))
                    ++_parent;
                return *this;
            }

            virtual const T &operator*() {
                return *_parent;
            }

        private:
            enumerator<T> &_parent;
            F _func;
        };

    } // namespace impl

    template<typename T>
    auto from(T begin, T end) {
        return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
    }

} // namespace linq

#endif
