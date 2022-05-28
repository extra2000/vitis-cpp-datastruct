/*
 * engine.ipp
 */

template < class Tx, class Ty, class Tresult >
myengine::MyEngine< Tx, Ty, Tresult >::MyEngine()
{
    log.init("engine");
    x = 0;
    y = 0;

    log.debug("Engine initialized");
}

template < class Tx, class Ty, class Tresult >
myengine::MyEngine< Tx, Ty, Tresult >::~MyEngine()
{
    log.debug("Engine destroyed");
}

template < class Tx, class Ty, class Tresult >
void myengine::MyEngine< Tx, Ty, Tresult >::set_x(Tx x)
{
    this->x = x;
    log.debug(boost::format("x is set to %1%") % this->x);
}

template < class Tx, class Ty, class Tresult >
void myengine::MyEngine< Tx, Ty, Tresult >::set_y(Ty y)
{
    this->y = y;
    log.debug(boost::format("y is set to %1%") % this->y);
}

template <class Tx, class Ty, class Tresult >
Tresult myengine::MyEngine< Tx, Ty, Tresult >::compute()
{
    Tresult result = x + y;
    log.debug(boost::format("Compute: %1% + %2% = %3%") % x % y % result);
    return result;
}
