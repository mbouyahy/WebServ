/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:45:11 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/14 12:48:37 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::vector<std::vector<std::string> >  HttpRequests::RequestData;
std::vector<std::string>                HttpRequests::SingleRequest;
std::string                             HttpRequests::RequestLine;
std::string                             HttpRequests::Method;

// HttpRequests();
// ~HttpRequests();
// HttpRequests(const HttpRequests &other);
// HttpRequests &operator=(const HttpRequests &other);

std::vector<std::string> SplitRequest(std::string data)
{
    std::istringstream s(data);
    std::vector<std::string> Lines;
    std::string Line;
    
    while (std::getline(s, Line))//check for CRLF | CR | LF
    {
        std::cout << "+ : " << Line << std::endl;
        Lines.push_back(Line);
    }
    return (Lines);
}

std::string  GetRequestLine(std::vector<std::string> Lines)
{
    if (Lines.size() > 0)
        HttpRequests::RequestLine = *(Lines.begin());
    return (HttpRequests::RequestLine);
}

std::string  FillLines(std::vector<std::vector<std::string> >  Requests)
{
    (void)Requests;
    // std::string _RequestLine;
    for (std::vector<std::vector<std::string> >::iterator iter = HttpRequests::RequestData.begin() ; iter != HttpRequests::RequestData.end(); iter++)
    {
        for (std::vector<std::string>::iterator SimpleIter = iter->begin(); SimpleIter != iter->end(); SimpleIter++)
        {
            std::vector<std::string> Lines = SplitRequest(*SimpleIter);//test
            GetRequestLine(Lines);
            // std::cout << "RequestLine : " << HttpRequests::RequestLine << std::endl;
        }
    }
    return (HttpRequests::RequestLine);
}

// void    HttpRequests::StoreRequest(std::string    _readStr)//i don't need this function
// {
//     // std::vector<std::string>    SingleRequest;

//     HttpRequests::SingleRequest.push_back(_readStr);
//     // HttpRequests::Requests.push_back(SingleRequest);
//     // std::cout << _readStr << "   SIze : " << HttpRequests::Requests.size() << std::endl;
// }

void PrintData(std::vector<std::vector<std::string> >  RequestData)
{
    for (std::vector<std::vector<std::string> >::iterator iter = RequestData.begin() ; iter != RequestData.end(); iter++)
    {
        for (std::vector<std::string>::iterator SimpleIter = iter->begin() ; SimpleIter != iter->end(); SimpleIter++)
        {
            std::cout << "* : " << *SimpleIter << std::endl;
        }
    }
}