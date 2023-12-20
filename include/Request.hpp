/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:17:44 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/20 17:33:56 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP


//change the name of file to HttpRequests or the reverse
#include <iostream>
#include <vector>
#include <map>
// #include <list> 
#include <sstream>
#include <string>

//define macros for checking methods
#define GET 0
#define POST 1
#define DELETE 2
// #define HEAD 3
#define INCORRECT -1

//The CRLF is the standard line ending sequence in HTTP.
#define CRLF "\r\n" //Carriage Return && Line Feed


#define LF "\n" // Line Feed


#define CR "\r" // Carriage Return

#define BlankLine "" // Blank Line

//URI_CHARACTERS macros for checking if URI is Correct or not  
#define URI_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%"

class HttpRequests
{
    private:
        // std::vector<std::vector<std::string> >                      RequestData;
        // std::vector<std::string>                                    SingleRequest;
        std::map<std::string, std::string>                          Header;
        std::vector<std::pair<std::string, std::string> >           Body;
        std::string                                                 Method;
        int                                                         ErrorCode;
        int                                                         BodyStartPosition;
        int                                                         ContentLength;
        std::string                                                 TransferEncoding;
        std::string                                                 Referer;//favicon.ico!!
        std::string                                                 RequestLine;
        std::string                                                 HTTPVersion;
        std::string                                                 RequestURI;//( / , /nameofpage, )
        std::string                                                 ContentType;//
        std::string                                                 Connection;//
        // std::vector<std::string>                                    Lines;
    public:
        HttpRequests();
        ~HttpRequests();
        HttpRequests(const HttpRequests &other);
        HttpRequests &operator=(const HttpRequests &other);


        //Getters
        std::string                             GetTransferEncoding() const;
        // std::vector<std::vector<std::string> >  GetRequestData() const;
        std::string                             GetRequestURI() const;
        std::string                             GetRequestLine() const;
        std::string                             GetHTTPVersion() const;
        std::string                             GetMethod() const;
        std::string                             GetContentType() const;
        std::string                             GetConnection() const;
        int                                     GetErrorCode() const;
        int                                     GetContentLength() const;
        std::map<std::string, std::string>      GetHeader() const;
        std::vector<std::pair<std::string, std::string> >   GetBody() const;
        
        //Setters
        void                                    SetTransferEncoding(std::string value);
        // void                                    SetRequestData(std::vector<std::vector<std::string> > value);
        void                                    SetRequestURI(std::string value);
        void                                    SetRequestLine(std::string value);
        void                                    SetHTTPVersion(std::string value);
        void                                    SetMethod(std::string value);
        void                                    SetConnection(std::string value);
        void                                    SetErrorCode(int value);
        void                                    SetContentLength(int value);
        void                                    SetContentType(std::string value);
        void                                    SetHeader(std::map<std::string, std::string> value);
        void                                    SetBody(std::vector<std::pair<std::string, std::string> > value);

        // std::vector<std::vector<std::string> >                      RequestData;
        // std::vector<std::string>                                    SingleRequest;
        std::vector<std::string>                                    Lines;
        std::string                                                 AllBody;//testing
        
        // static std::vector<std::vector<std::string> >   RequestData;
        // static std::vector<std::string>                 SingleRequest;
        // static int                                      Method;
        // static int                                      ErrorCode;

        // static std::string RequestLine;//Request-Line = Method SP Request-URI SP HTTP-Version CRLF
        /*
            Transfer-Encoding: chunked
            Transfer-Encoding: compress
            Transfer-Encoding: deflate
            Transfer-Encoding: gzip

            // Several values can be listed, separated by a comma
            Transfer-Encoding: gzip, chunked
        */
        // static std::string TransferEncoding;
        // static std::string Referer;//favicon.ico!!
        // static std::string RequestURI;//( / , /nameofpage, )


        //Member Functions
        void SplitLine(std::string Line);
        std::vector<std::string> SplitRequest(std::string data);
        // std::string  FillLines(std::vector<std::vector<std::string> >  Requests);
        void FillRequestURI();
        std::string  FillRequestLine();//change this and work with SearchLine();
        bool    iSValidURI();

};

// std::string     FillLines(std::vector<std::vector<std::string> >  Requests);
HttpRequests *    FillLines(std::vector<std::string>    SingleRequest);
void            PrintData(std::vector<std::vector<std::string> >  RequestData);
// std::string     GetRequestLine(std::vector<std::string> Lines);

#endif