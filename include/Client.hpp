/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:39:23 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/19 15:04:24 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Client_HPP
#define Client_HPP

#include "Request.hpp"

class   Client
{
	// std::string     _readStr;
    // private:
    //     std::map<int, Client *>					ClientsInformation;
    public:
        Client();
        ~Client();
        Client(const Client &other);
        Client &operator=(const Client &other);
        // int             sd;
        HttpRequests    *ClientRequest;
        
        // void            SetMap(int sd, Client *Obj);
        // bool            SearchInMap(int sd);
        // HttpRequests    GetClientRequest(int sd);
	// Response;
};

#endif