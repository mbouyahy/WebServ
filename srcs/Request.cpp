/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:45:11 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/20 20:05:36 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

// void    PrintVectorOfPairs(std::vector<std::pair<std::string, std::string> >           Body);

HttpRequests::HttpRequests(){ }

HttpRequests::~HttpRequests(){}

HttpRequests::HttpRequests(const HttpRequests &other){ (void)other; }

HttpRequests &HttpRequests::operator=(const HttpRequests &other)
{
    if (this != &other){}
    return (*this);
}

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


void                                                HttpRequests::SetBody(std::vector<std::pair<std::string, std::string> > value){ Body = value; }

void                                                HttpRequests::SetRequestURI(std::string value) { RequestURI = value; }

void                                                HttpRequests::SetRequestLine(std::string value) { RequestLine= value; }

void                                                HttpRequests::SetHTTPVersion(std::string value) { HTTPVersion = value; }

void                                                HttpRequests::SetMethod(std::string value) { Method = value; }

void                                                HttpRequests::SetErrorCode(int value) { ErrorCode = value; }

void                                                HttpRequests::SetHeader(std::map<std::string, std::string> value) { Header = value; }

void                                                HttpRequests::SetContentType(std::string value) { ContentType = value; }

void                                                HttpRequests::SetContentLength(int value) {ContentLength = value;}

void                                                HttpRequests::SetConnection(std::string value){ Connection = value; }

bool SearchLine(std::string Line, std::string Content)
{
    if (Line.find(Content) <= Line.size())
        return (true);
    return (false);
}

bool    HttpRequests::iSValidURI()
{
   std::string  uri_Characters;
   
   uri_Characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
   for (size_t i = 0; i < RequestURI.size(); i++)
   {
       if (uri_Characters.find(RequestURI[i], 0) > uri_Characters.size())
       {
            //400 => Bad Request | Uploading a file that is too large | Invalid Cookies | DNS cache error
            ErrorCode = 400;
            return (false);
       }
   }
   //check the size of URI (limit it in 2,048 characters!!!) | 414 URI Too Long
   if (RequestURI.size() > 2048)//I'm Not Sure About That
       ErrorCode = 414;
   return (true);
}

void HttpRequests::SplitLine(std::string Line)
{
    size_t          begin;
    std::string     Value;
    std::string     Key;

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
    size_t          begin;
    size_t          end;

    begin = RequestLine.find(" ");
    if (begin >= RequestLine.size())
        return ;
    end = RequestLine.find(" ", begin + 1);
    if (end >= RequestLine.size())
        return ;
    for (size_t i = begin + 1; i < end; i++)
        RequestURI += RequestLine[i];
    for (size_t i = 0; i < begin; i++)
        Method += RequestLine[i];
    for (size_t i = end + 1; i < RequestLine.size(); i++)
        HTTPVersion += RequestLine[i];
    if (!iSValidURI())
        return ;//return error code
}

std::vector<std::string> HttpRequests::SplitRequest(std::string data)
{
    std::istringstream          s(data);
    std::vector<std::string>    Lines;
    std::string                 Line;
    int                         i;

    i = 0;
    while (std::getline(s, Line))//check for CRLF | CR | LF
    {
        if (i > 0)
            SplitLine(Line);
        Lines.push_back(Line);
        i++;
    }
    return (Lines);
}

std::string  HttpRequests::FillRequestLine()//change this and work with SearchLine()
{
    //Request-Line = Method SP Request-URI SP HTTP-Version CRLF
    if (Lines.size() > 0)
        RequestLine = *(Lines.begin());
    return (RequestLine);
}

void OrganizeContentType(HttpRequests *Request)
{
    bool                                                Status;
    std::string                                         Line;
    std::string                                         Key;
    std::string                                         Value;
    std::vector<std::pair<std::string, std::string> >   Body;
    std::istringstream                                  ss(Request->AllBody);

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
}

void    ConvertBodyToKeyValue(HttpRequests *Request)
{
    if (Request->GetContentType() == "application/x-www-form-urlencoded")
        OrganizeContentType(Request);
}

void FillBody(HttpRequests *Request, std::string data)
{
    size_t begin;
    
    begin = data.find("\r\n\r\n");
    if (begin > data.size())
        return;
    for (size_t i = begin; i < data.size(); i++)
    {
        if ((data[i] == '\r' || data[i] == '\n') && Request->AllBody == "")
            continue;
        Request->AllBody += data[i];
    }
    ConvertBodyToKeyValue(Request);
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
    }
    return (Request);
}

bool    SearchSd(std::map<int, Client *>	*ClientsInformation, int sd)
{
    std::__1::map<int, Client *>::iterator iter;
	for (iter = ClientsInformation->begin(); iter != ClientsInformation->end(); iter++)
	{
        if (iter->first == sd)
            return (true);
    }
    return (false);
}

void	HandleRequest(std::string _readStr, int sd, std::map<int, Client *>	*ClientsInformation, Client *_Client)
{
	HttpRequests				*Request;
	std::vector<std::string>	SingleRequest;

	Request = new HttpRequests();
	SingleRequest.push_back(_readStr);
	Request = FillLines(SingleRequest);
	_Client->ClientRequest = Request;
	ClientsInformation->insert(std::make_pair(sd, _Client));
	PrintMap(ClientsInformation);
}

void    HttpRequests::PrintVectorOfPairs(std::vector<std::pair<std::string, std::string> >           Body)
{
    std::vector<std::pair<std::string, std::string> >::iterator           iter;
    for (iter = Body.begin(); iter != Body.end(); iter++)
        std::cout << "Key : " << iter->first << " | Value : " << iter->second << std::endl;
}

void PrintData(std::vector<std::vector<std::string> >  RequestData)
{
    for (std::vector<std::vector<std::string> >::iterator iter = RequestData.begin() ; iter != RequestData.end(); iter++)
        for (std::vector<std::string>::iterator SimpleIter = iter->begin() ; SimpleIter != iter->end(); SimpleIter++)
            std::cout << "* : " << *SimpleIter << std::endl;
}