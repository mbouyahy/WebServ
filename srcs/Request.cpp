/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:45:11 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/20 19:01:54 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

// std::vector<std::vector<std::string> >  HttpRequests::RequestData;
// std::vector<std::string>                HttpRequests::SingleRequest;
// std::string                             HttpRequests::RequestLine;
// int                                     HttpRequests::Method;
// int                                     HttpRequests::ErrorCode;
// std::string                             HttpRequests::RequestURI;
// std::list<HttpRequests::header>         HttpRequests::headers;
void    PrintVectorOfPairs(std::vector<std::pair<std::string, std::string> >           Body);
HttpRequests::HttpRequests()
{ 
}

HttpRequests::~HttpRequests()
{ 
}

HttpRequests::HttpRequests(const HttpRequests &other)
{
    (void)other;
}

HttpRequests &HttpRequests::operator=(const HttpRequests &other)
{
    if (this != &other)
    {
        
    }
    return (*this);
}

// std::string                             HttpRequests::GetTransferEncoding()
// std::vector<std::vector<std::string> >  HttpRequests::GetRequestData();

std::vector<std::pair<std::string, std::string> >   HttpRequests::GetBody() const{ return (Body); }
std::map<std::string, std::string>                  HttpRequests::GetHeader() const { return (Header); }
std::string                                         HttpRequests::GetRequestURI() const { return (RequestURI); }
std::string                                         HttpRequests::GetRequestLine() const { return (RequestLine); }
std::string                                         HttpRequests::GetHTTPVersion() const { return (HTTPVersion); }
std::string                                         HttpRequests::GetMethod() const { return (Method); }
std::string                                         HttpRequests::GetConnection() const { return (Connection); }
std::string                                         HttpRequests::GetContentType() const { return (ContentType); };
int                                                 HttpRequests::GetErrorCode() const { return (ErrorCode); }
int                                                 HttpRequests::GetContentLength() const { return (ContentLength); }

// void                                    SetTransferEncoding(std::string value);
// void                                    SetRequestData(std::vector<std::vector<std::string> > value);
void                                    HttpRequests::SetBody(std::vector<std::pair<std::string, std::string> > value){ Body = value; }
void                                    HttpRequests::SetRequestURI(std::string value) { RequestURI = value; }
void                                    HttpRequests::SetRequestLine(std::string value) { RequestLine= value; }
void                                    HttpRequests::SetHTTPVersion(std::string value) { HTTPVersion = value; }
void                                    HttpRequests::SetMethod(std::string value) { Method = value; }
void                                    HttpRequests::SetErrorCode(int value) { ErrorCode = value; }
void                                    HttpRequests::SetHeader(std::map<std::string, std::string> value) { Header = value; }
void                                    HttpRequests::SetContentType(std::string value) { ContentType = value; }
void                                    HttpRequests::SetContentLength(int value) {ContentLength = value;}
void                                    HttpRequests::SetConnection(std::string value){ Connection = value; }

bool SearchLine(std::string Line, std::string Content)
{
    if (Line.find(Content) <= Line.size())
        return (true);
    return (false);
}

//initData();

bool    HttpRequests::iSValidURI()
{
   std::string uri_Characters 
   = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
   for (size_t i = 0; i < RequestURI.size(); i++)
   {
       if (uri_Characters.find(RequestURI[i], 0) > uri_Characters.size())
       {
            //400 => Bad Request | Uploading a file that is too large | Invalid Cookies | DNS cache error
           ErrorCode = 400;
            return (false);
       }
   }
   if (RequestURI.size() > 2048)
       ErrorCode = 414;
   //check the size of URI (limit it in 2,048 characters) | 414 URI Too Long
   return (true);
}

// void    FillMethod(std::string method)
// {
//     method == "GET" ? HttpRequests::Method = GET : (method == "POST" ? HttpRequests::Method = POST : (method == "DELETE" ? HttpRequests::Method = DELETE : HttpRequests::Method = INCORRECT));
// }

// void PrintList()
// {
//     std::list<HttpRequests::header>::iterator iter;
//     std::list< std::pair<std::string, std::string> >::iterator L_iter;

//     for (iter = HttpRequests::headers.begin(); iter != HttpRequests::headers.end(); iter++)
//     {
//         for (L_iter = iter->begin(); L_iter != iter->end(); L_iter++)
//         {
//             std::cout << "Key : " << L_iter->first << std::endl;
//             std::cout << "Value : " << L_iter->second << std::endl;
//         }
//     }
// }

void HttpRequests::SplitLine(std::string Line)
{
    size_t          begin;
    std::string     Key;
    std::string     Value;

    if (Line.empty())
        return ;
    begin = Line.find(":");
    if (begin >= Line.size())
    {
        HttpRequests::ErrorCode = 1;
        return ;
    }
    for (size_t i = 0; i < begin; i++)
        Key += Line[i];
    for (size_t i = begin + 2; i < Line.size(); i++)//skep (:Space)
    {
        if (Line[i] == '\n' || Line[i] == '\r')
            break ;
        Value += Line[i];
    }
    if (SearchLine(Line, "Content-Type"))
        ContentType = Value;
    if (SearchLine(Line, "Content-Length"))
        ContentLength = static_cast<int>(strtod(Value.c_str(), NULL));
    if (SearchLine(Line, "Connection"))
        Connection = Value;
    Header.insert(std::make_pair(Key, Value));
}

void HttpRequests::FillRequestURI()
{
    // std::string     HTTPVersion;
    size_t          begin;
    size_t          end;

    // if (RequestLine.empty())
    //     return ;
    begin = RequestLine.find(" ");
    if (begin >= RequestLine.size())
        return ;
    end = RequestLine.find(" ", begin + 1);
    if (end >= RequestLine.size())
        return ;
    // if (ErrorCode == 1)
    //     return ;
    for (size_t i = begin + 1; i < end; i++)
        RequestURI += RequestLine[i];
    for (size_t i = 0; i < begin; i++)
        Method += RequestLine[i];
    for (size_t i = end + 1; i < RequestLine.size(); i++)
        HTTPVersion += RequestLine[i];
    if (!iSValidURI())
        return ;//return error code
    // FillMethod(method);
    // std::cout << "* HTTPVersion : " << HTTPVersion << "\n Size : " << HTTPVersion.size() << std::endl;
    // std::cout << "* URI : " << HttpRequests::RequestLine << std::endl;
    // std::cout << "**** Method : " << method << " HttpRequests::Method value : " << HttpRequests::Method << " Size : " << method.size() << std::endl;
    // std::cout << "* IsValidURI : " << iSValidURI() << std::endl;
}

std::vector<std::string> HttpRequests::SplitRequest(std::string data)
{
    std::istringstream s(data);
    std::vector<std::string> Lines;
    std::string Line;
    int i = 0;
    // BodyStartPosition = 0;
    while (std::getline(s, Line))//check for CRLF | CR | LF
    {
        if (i > 0)
            SplitLine(Line);
        Lines.push_back(Line);
        // std::cout << "+ : " << Line << std::endl;
        i++;
    }
    return (Lines);
}

std::string  HttpRequests::FillRequestLine()//change this and work with SearchLine()
{
    if (Lines.size() > 0)
        RequestLine = *(Lines.begin());
    return (RequestLine);
}

void OrganizeContentType(HttpRequests *Request)
{
    (void)Request;
    std::string Line;
    std::string Key;
    std::string Value;
    bool Status;
    std::istringstream ss(Request->AllBody);
    std::vector<std::pair<std::string, std::string> >           Body;

    while (getline(ss, Line, '&'))
    {
        std::istringstream s(Line);
        Status = false;
        Value = "";
        Key = "";
        while (getline(s, Line, '='))
        {
            Status ? Value = Line : Key = Line;
            Status = true;
        }
        Body.push_back(std::make_pair(Key, Value));
    }
    Request->SetBody(Body);
    PrintVectorOfPairs(Request->GetBody());
}

void    ConvertBodyToKeyValue(HttpRequests *Request)
{
    if (Request->GetContentType() == "application/x-www-form-urlencoded")
        OrganizeContentType(Request);
}

void FillBody(HttpRequests *Request, std::string data)
{
    (void)Request;
    (void)data;
    // std::cout << "<---------------Request Begin----------------->" << std::endl;
    // std::cout << data << std::endl;
    // std::cout << "<---------------Request End----------------->" << std::endl;
    
    std::cout << "\n<---------------Body Begin----------------->" << std::endl;
    size_t begin = data.find("\r\n\r\n");
    if (begin > data.size())
        return;
    for (size_t i = begin; i < data.size(); i++)
    {
        if ((data[i] == '\r' || data[i] == '\n') && Request->AllBody == "")
            continue;
        // std::cout << "data[" << i << "] : "<< static_cast<int>(data[i]) << std::endl;
        // std::cout << data[i];
        Request->AllBody += data[i];
    }
    std::cout << Request->AllBody << std::endl;
    ConvertBodyToKeyValue(Request);
    std::cout << "\n<---------------Body Begin----------------->" << std::endl;
}

HttpRequests *    FillLines(std::vector<std::string>    SingleRequest)
{
    HttpRequests *Request = new HttpRequests();
    
    for (std::vector<std::string>::iterator SimpleIter = SingleRequest.begin(); \
            SimpleIter != SingleRequest.end(); SimpleIter++)//i will remove this later
    {
        Request->Lines = Request->SplitRequest(*SimpleIter);//test
        Request->FillRequestLine();
        Request->FillRequestURI();
        if (Request->GetMethod() == "POST")
            FillBody(Request, *SimpleIter);
        // std::cout << "***** Connection : " << Request->GetConnection() << std::endl;
        // std::cout << "***** Content Type : " << Request->GetContentType() << std::endl;
        // std::cout << "***** Content Length : " << Request->GetContentLength() << std::endl;
        // Request->RequestURI = "";
        // std::cout << "Method : " << Request->GetMethod() << std::endl;
        // std::cout << "Return Value : " << SearchLine(HttpRequests::RequestLine, "GET") << std::endl;
    }
    return (Request);
}

void    PrintVectorOfPairs(std::vector<std::pair<std::string, std::string> >           Body)
{
    // std::vector<std::pair<std::string, std::string> >           Body;
    std::vector<std::pair<std::string, std::string> >::iterator           iter;
    // Body = Request->GetBody();
    for (iter = Body.begin(); iter != Body.end(); iter++)
    {
        std::cout << "Key : " << iter->first << " | Value : " << iter->second << std::endl;
    }
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