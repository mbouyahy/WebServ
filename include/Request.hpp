/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:17:44 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/20 19:40:14 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

//change the name of file to HttpRequests or the reverse
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Client.hpp"
class Client;

//define macros for checking methods
#define GET 0
#define POST 1
#define DELETE 2
#define INCORRECT -1

//The CRLF is the standard line ending sequence in HTTP.
#define CRLF "\r\n" //Carriage Return && Line Feed
#define LF "\n" // Line Feed
#define CR "\r" // Carriage Return

class HttpRequests
{
    private:
        std::vector<std::pair<std::string, std::string> >           Body;
        std::map<std::string, std::string>                          Header;
        std::string                                                 Method;
        int                                                         ErrorCode;
        int                                                         BodyStartPosition;
        int                                                         ContentLength;
        std::string                                                 TransferEncoding;
        std::string                                                 RequestLine;
        std::string                                                 HTTPVersion;
        std::string                                                 RequestURI;
        std::string                                                 ContentType;
        std::string                                                 Connection;
    public:
        HttpRequests();
        ~HttpRequests();
        HttpRequests(const HttpRequests &other);
        HttpRequests &operator=(const HttpRequests &other);


        //Getters
        std::map<std::string, std::string>                          GetHeader() const;
        std::vector<std::pair<std::string, std::string> >           GetBody() const;
        int                                                         GetErrorCode() const;
        int                                                         GetContentLength() const;
        std::string                                                 GetTransferEncoding() const;
        std::string                                                 GetRequestURI() const;
        std::string                                                 GetRequestLine() const;
        std::string                                                 GetHTTPVersion() const;
        std::string                                                 GetMethod() const;
        std::string                                                 GetContentType() const;
        std::string                                                 GetConnection() const;
        
        //Setters
        void                                                        SetTransferEncoding(std::string value);
        void                                                        SetRequestURI(std::string value);
        void                                                        SetRequestLine(std::string value);
        void                                                        SetHTTPVersion(std::string value);
        void                                                        SetMethod(std::string value);
        void                                                        SetConnection(std::string value);
        void                                                        SetErrorCode(int value);
        void                                                        SetContentLength(int value);
        void                                                        SetContentType(std::string value);
        void                                                        SetHeader(std::map<std::string, std::string> value);
        void                                                        SetBody(std::vector<std::pair<std::string, std::string> > value);

        
        std::vector<std::string>                                    Lines;
        std::string                                                 AllBody;

        //Member Functions
        std::vector<std::string>                                    SplitRequest(std::string data);
        std::string                                                 FillRequestLine();//change this and work with SearchLine();
        void                                                        SplitLine(std::string Line);
        void                                                        FillRequestURI();
        bool                                                        iSValidURI();

        //Functions For Testing Only
        void                                                        PrintVectorOfPairs(std::vector<std::pair<std::string, std::string> >    Body);
};

HttpRequests                                                        *FillLines(std::vector<std::string>    SingleRequest);
void                                                                PrintData(std::vector<std::vector<std::string> >  RequestData);
void                                                                HandleRequest(std::string _readStr, int sd, std::map<int, Client *>	*ClientsInformation, Client *_Client);

#endif