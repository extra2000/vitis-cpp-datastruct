/*
 * engine.ipp
 */

template < class T >
myengine::MyEngine< T >::MyEngine()
{
    log.init("engine");
    saving = 0.0;
    log.debug("Engine initialized");
}

template < class T >
myengine::MyEngine< T >::~MyEngine()
{
    log.debug("Engine destroyed");
}

template < class T >
void myengine::MyEngine< T >::deposit(T amount)
{
    log.debug(boost::format("Deposit %.1000f into current saving %.1000f") % amount % saving);
    saving += amount;
    log.debug(boost::format("Deposit success. New saving is %.1000f") % saving);
}

template < class T >
void myengine::MyEngine< T >::withdraw(T amount)
{
    log.debug(boost::format("Withdraw %.1000f from current saving %.1000f") % amount % saving);
    if (amount <= saving)
    {
        saving -= amount;
        log.debug(boost::format("Withdraw success. New saving is %.1000f") % saving);
    }
    else
    {
        log.error(boost::format("Withdraw amount %.1000f is more than saving %.1000f") % amount % saving);
        throw(std::invalid_argument( (boost::format("Withdraw amount %.1000f is more than saving %.1000f") % amount % saving).str() ));
    }
}
