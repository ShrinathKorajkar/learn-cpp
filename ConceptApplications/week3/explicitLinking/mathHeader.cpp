extern "C"
{
    namespace math
    {
        int add(const int &value1, const int &value2)
        {
            return value1 + value2;
        }

        int subtract(const int &value1, const int &value2)
        {
            return value1 - value2;
        }

        int multiply(const int &value1, const int &value2)
        {
            return value1 * value2;
        }

        int divide(const int &value1, const int &value2)
        {
            return value1 / value2;
        }
    }
}