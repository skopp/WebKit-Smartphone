/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "WebHistoryClient.h"

#include "WKAPICast.h"
#include "WebNavigationData.h"
#include <wtf/RefPtr.h>

using namespace WebCore;

namespace WebKit {

WebHistoryClient::WebHistoryClient()
{
    initialize(0);
}

void WebHistoryClient::initialize(const WKContextHistoryClient* client)
{
    if (client && !client->version)
        m_contextHistoryClient = *client;
    else 
        memset(&m_contextHistoryClient, 0, sizeof(m_contextHistoryClient));
}

void WebHistoryClient::didNavigateWithNavigationData(WebContext* context, WebPageProxy* page, const WebNavigationDataStore& navigationDataStore, WebFrameProxy* frame)
{
    if (!m_contextHistoryClient.didNavigateWithNavigationData)
        return;

    RefPtr<WebNavigationData> navigationData = WebNavigationData::create(navigationDataStore); 
    m_contextHistoryClient.didNavigateWithNavigationData(toRef(context), toRef(page), toRef(navigationData.get()), toRef(frame), m_contextHistoryClient.clientInfo);
}

void WebHistoryClient::didPerformClientRedirect(WebContext* context, WebPageProxy* page, const String& sourceURL, const String& destinationURL, WebFrameProxy* frame)
{
    if (!m_contextHistoryClient.didPerformClientRedirect)
        return;

    m_contextHistoryClient.didPerformClientRedirect(toRef(context), toRef(page), toURLRef(sourceURL.impl()), toURLRef(destinationURL.impl()), toRef(frame), m_contextHistoryClient.clientInfo);
}

void WebHistoryClient::didPerformServerRedirect(WebContext* context, WebPageProxy* page, const String& sourceURL, const String& destinationURL, WebFrameProxy* frame)
{
    if (!m_contextHistoryClient.didPerformServerRedirect)
        return;

    m_contextHistoryClient.didPerformServerRedirect(toRef(context), toRef(page), toURLRef(sourceURL.impl()), toURLRef(destinationURL.impl()), toRef(frame), m_contextHistoryClient.clientInfo);
}

void WebHistoryClient::didUpdateHistoryTitle(WebContext* context, WebPageProxy* page, const String& title, const String& url, WebFrameProxy* frame)
{
    if (!m_contextHistoryClient.didUpdateHistoryTitle)
        return;

    m_contextHistoryClient.didUpdateHistoryTitle(toRef(context), toRef(page), toRef(title.impl()), toURLRef(url.impl()), toRef(frame), m_contextHistoryClient.clientInfo);
}

void WebHistoryClient::populateVisitedLinks(WebContext* context)
{
    if (!m_contextHistoryClient.populateVisitedLinks)
        return;

    m_contextHistoryClient.populateVisitedLinks(toRef(context), m_contextHistoryClient.clientInfo);
}

} // namespace WebKit
