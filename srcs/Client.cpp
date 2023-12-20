/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyahy <mbouyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:39:10 by mbouyahy          #+#    #+#             */
/*   Updated: 2023/12/19 14:08:52 by mbouyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client()
{

}

Client::~Client()
{

}

Client::Client(const Client &other)
{
    (void)other;
}

Client &Client::operator=(const Client &other)
{
    if (this != &other)
    {

    }
    return (*this);
}

// void            Client::SetMap(int sd, Client *Obj)
// {
//     ClientsInformation.insert(std::make_pair(sd, Obj));
// }

// bool            Client::SearchInMap(int sd)
// {
//     // if (ClientsInformation.find(sd) <= ClientsInformation.size())
//         // return (true);
//     return (false);
// }

// HttpRequests    Client::GetClientRequest(int sd)
// {
    
// }