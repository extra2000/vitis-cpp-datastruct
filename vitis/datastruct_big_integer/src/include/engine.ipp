/*
 * engine.ipp
 */

template < class T >
myengine::MyEngine< T >::MyEngine()
{
    log.init("engine");
    log.debug("Engine initialized");
}

template < class T >
myengine::MyEngine< T >::~MyEngine()
{
    log.debug("Engine destroyed");
}

template < class T >
void myengine::MyEngine< T >::compute_factorial(unsigned int max_bitsize)
{
    log.debug(boost::format("Finding the largest factorial for %1% bit integer") % max_bitsize);
    T limit = (T(1) << max_bitsize) - 1;

    T factorial = 1;
    unsigned int i = 0;
    while(factorial < limit)
    {
        ++i;
        factorial *= i;
        log.debug(boost::format("iteration = %1% ; factorial = %2%") % i % factorial);
        result = (factorial < limit) ? factorial : result;
    }

    log.debug(boost::format("Factorial %1% exceed limit %2%. Thus, the largest factorial for %3% bit integer is %4%") % factorial % limit % max_bitsize % result);
}

template < class T >
T myengine::MyEngine< T >::get_result() const
{
    return result;
}
