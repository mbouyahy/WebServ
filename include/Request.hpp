/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:17:44 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/14 11:57:01 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

//define macros for checking methods
#define GET 0
#define POST 1
#define DELETE 2
#define HEAD 3
#define INCORRECT -1

//The CRLF is the standard line ending sequence in HTTP.
//Carriage Return && Line Feed
#define CRLF "\r\n"

// Line Feed
#define LF "\n"

// Carriage Return
#define CR "\r"

//URI_CHARACTERS macros for checking if URI is Correct or not  
#define URI_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%"

class HttpRequests
{
    public:
        HttpRequests();
        ~HttpRequests();
        HttpRequests(const HttpRequests &other);
        HttpRequests &operator=(const HttpRequests &other);
        
        static std::vector<std::vector<std::string> >   RequestData;
        static std::vector<std::string>                 SingleRequest;
        static std::string                              Method;

        static std::string RequestLine;//Request-Line = Method SP Request-URI SP HTTP-Version CRLF

        // static void    StoreRequest(std::string    _readStr);
};
std::string     FillLines(std::vector<std::vector<std::string> >  Requests);
void            PrintData(std::vector<std::vector<std::string> >  RequestData);
// std::string     GetRequestLine(std::vector<std::string> Lines);

#endif