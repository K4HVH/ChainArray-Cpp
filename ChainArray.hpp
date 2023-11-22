template<typename T>
class ChainArray {
public:
    class iterator : public std::iterator<std::input_iterator_tag, T> {
    public:
        explicit iterator(const ChainArray& ca, const std::vector<T>& values) : ca(ca), values(values), currentIteration(0) {}

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

    // Constructor with array input
    ChainArray(const std::vector<T>& values, size_t iterations) : values(values), iterations(iterations) {}

    iterator begin() const {
        return iterator(*this, values);
    }

    iterator end() const {
        iterator iter(*this, values);
        // Check if the current iteration exceeds the size of the input array
        iter.currentIteration = std::min(iterations, values.size());
        return iter;
    }

private:
    std::vector<T> values;
    size_t iterations;
};
