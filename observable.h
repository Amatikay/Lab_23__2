//
// Created by sergey on 21.05.22.
//

#ifndef LAB_23__2_OBSERVABLE_H
#define LAB_23__2_OBSERVABLE_H


#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <set>
#include <vector>

template< class Observer >
class Observable {
public:
    virtual ~Observable() {
    }

    void registerObserver( Observer* observer ) {
        if( m_count != 0 ) {
            m_requests.push_back( ObserverRequest { &Observable< Observer >::registerObserver, observer } );
        } else if( observer ) {
            m_observers.insert( observer );
        }
    }

    void unregisterObserver( Observer* observer ) {
        if( m_count != 0 ) {
            m_requests.push_back( ObserverRequest { &Observable< Observer >::unregisterObserver, observer } );
        } else if( observer ) {
            m_observers.erase( observer );
        }
    }

protected:
    Observable() : m_count( 0 ) {
    }

    template< typename F, typename... Args >
    void notifyObservers( F f, Args... args ) {
        ++m_count;
        for( Observer* o : m_observers ) {
            ( o->*f )( args... );
        };
        --m_count;
        if( m_count == 0 ) {
            for( const ObserverRequest& r : m_requests ) {
                ( this->*r.operation )( r.observer );
            };
            m_requests.clear();
        }
    }

private:
    struct ObserverRequest {
        void ( Observable< Observer >::*operation )( Observer* );
        Observer* observer;
    };

    std::set< Observer* > m_observers;
    int m_count;
    std::vector< ObserverRequest > m_requests;
};

#endif // OBSERVABLE_H

#endif //LAB_23__2_OBSERVABLE_H
