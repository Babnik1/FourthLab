#pragma once

/// @file
///
/// Шаблонные функции вывода.
///

#include <type_traits>
#include <iostream>
#include <cstdint>


template< typename T >
struct isTuple : std::false_type {};

template< typename... Args >
struct isTuple< std::tuple< Args... > > : std::true_type {};

template < typename T >
inline constexpr bool is_tuple_v = isTuple< T >::value;

/// @brief Шаблонная функция предназанченная для контейнеров, содержащих итератор.
/// @param container Контейнер.
/// @return Ничего.
template< typename T >
auto print_ip( const T& container ) -> std::enable_if_t< 
                                                !std::is_same_v< typename T::value_type, char > &&
                                                !std::is_void< typename T::iterator >::value >
{
    bool first = true;
    for( const auto& c : container )
    {
        if ( !first )
        {
            printf( "." );
        }
        printf( "%d", c );
        first = false;
    }
    printf( "\n" );
};

/// @brief Шаблонная функция предназанченная для строк. 
/// @param str Строка.
/// @return Ничего.
template< typename T >
auto print_ip( const T& str ) -> std::void_t< decltype( std::declval< T >().c_str() ) > /// А самый простой способ, явно указать, что это строка через is_same
{
    printf( "%s\n", str.c_str() );
};

/// @brief Шаблонная функция для кортежей.
/// @param tpl Кортеж.
/// @return Ничего.
template< typename T >
auto print_ip( const T& tpl ) -> std::enable_if_t< is_tuple_v< T >, void >
{
    printf( "%d.%d.%d.%d\n", std::get< 0 >( tpl ), 
                             std::get< 1 >( tpl ),
                             std::get< 2 >( tpl ),
                             std::get< 3 >( tpl )
    );
};

/// @brief Шаблонная функция для беззнаковых чисел различного размера.
/// @param num Число.
/// @return Ничего.
template< typename T >
auto print_ip( const T& num ) -> std::enable_if_t< std::is_integral_v< T >, void >
{
    for ( int i = sizeof( T ) - 1; i >= 0; --i )
    {
        printf( "%d", static_cast< uint8_t >( num >> i * 8 ) );
        if ( i != 0 )
        {
            printf( "." );
        }
    }
    printf( "\n" );
};

