template<typename T>
class ChainArray {
public:
    class iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        explicit iterator(const ChainArray& ca, const std::vector<T>& values, size_t currentIteration)
            : ca(ca), values(values), currentIteration(currentIteration) {}

        T operator*() const {
            return values[currentIteration];
        }

        iterator& operator++() {
            ++currentIteration;
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return currentIteration != other.currentIteration;
        }

    private:
        const ChainArray& ca;
        const std::vector<T>& values;
        size_t currentIteration;

        friend class ChainArray;  // Allow ChainArray to access private members
    };

    // Constructor with array input and starting offset
    ChainArray(const std::vector<T>& values, size_t iterations, size_t offset = 0) : values(values), iterations(iterations), offset(std::min(offset, values.size() - 1)) {}

    iterator begin() const {
        return iterator(*this, values, offset);
    }

    iterator end() const {
        iterator iter(*this, values, std::min(offset + iterations, values.size()));
        return iter;
    }

private:
    std::vector<T> values;
    size_t iterations;
    size_t offset;
};
