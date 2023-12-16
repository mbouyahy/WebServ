/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:45:11 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/16 17:06:22 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

std::vector<std::vector<std::string> >  HttpRequests::RequestData;
std::vector<std::string>                HttpRequests::SingleRequest;
std::string                             HttpRequests::RequestLine;
int                                     HttpRequests::Method;
int                                     HttpRequests::ErrorCode;
std::string                             HttpRequests::RequestURI;

// HttpRequests();
// ~HttpRequests();
// HttpRequests(const HttpRequests &other);
// HttpRequests &operator=(const HttpRequests &other);

bool SearchLine(std::string Line, std::string Content)
{
    if (Line.find(Content) <= Line.size())
        return (true);
    return (false);
}

bool    iSValidURI()
{
   std::string uri_Characters 
   = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
   for (size_t i = 0; i < HttpRequests::RequestURI.size(); i++)
   {
       if (uri_Characters.find(HttpRequests::RequestURI[i], 0) > uri_Characters.size())
       {
            //400 => Bad Request | Uploading a file that is too large | Invalid Cookies | DNS cache error
            HttpRequests::ErrorCode = 400;
            return (false);
       }
   }
   if (HttpRequests::RequestURI.size() > 2048)
        HttpRequests::ErrorCode = 414;
   //check the size of URI (limit it in 2,048 characters) | 414 URI Too Long
   return (true);
}

void GetRequestURI(std::string RequestLine)
{
    size_t begin;
    size_t end;
    std::string method;

    begin = RequestLine.find(" ");
    if (begin >= RequestLine.size())
        HttpRequests::ErrorCode = 1;
    end = RequestLine.find(" ", begin + 1);
    if (end >= RequestLine.size())
        HttpRequests::ErrorCode = 1;
    for (size_t i = begin + 1; i < end; i++)
        HttpRequests::RequestURI += RequestLine[i];
    for (size_t i = 0; i < begin; i++)
        method += RequestLine[i];
    std::cout << "* URI : " << HttpRequests::RequestLine << std::endl;
    // std::cout << "**** Method : " << method << "Size : " << method.size() << std::endl;
    // std::cout << "* IsValidURI : " << iSValidURI() << std::endl;
}

std::vector<std::string> SplitRequest(std::string data)
{
    std::istringstream s(data);
    std::vector<std::string> Lines;
    std::string Line;
    
    while (std::getline(s, Line))//check for CRLF | CR | LF
    {
        // std::cout << "+ : " << Line << std::endl;
        Lines.push_back(Line);
    }
    return (Lines);
}

std::string  GetRequestLine(std::vector<std::string> Lines)//change this and work with SearchLine()
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
            GetRequestURI(HttpRequests::RequestLine);
            HttpRequests::RequestURI = "";
            // std::cout << "RequestLine : " << HttpRequests::RequestLine << std::endl;
            // std::cout << "Return Value : " << SearchLine(HttpRequests::RequestLine, "GET") << std::endl;
        }
    }
    return (HttpRequests::RequestLine);
}

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