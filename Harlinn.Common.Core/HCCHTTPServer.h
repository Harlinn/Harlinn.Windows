#pragma once
#ifndef __HCCHTTPSERVER_H__
#define __HCCHTTPSERVER_H__
/*
   Copyright 2024-2025 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <HCCHTTP.h>
#include <HCCMemory.h>
#include <HCCBlocks.h>

#pragma pack(push,8)
namespace Harlinn::Common::Core::Http::Server
{
    class HttpReceiveRequest;
    class HttpServer;
    class HttpServerRequestQueue;
    class HttpConnection;

    


    namespace Internal
    {
        enum class HttpRequestState
        {
            Unknown,
            New,
            Receiving,
            Received,
            BodyReceived,
            ResponseSent,
            ResponseBodySent
        };

        template<typename T>
        concept LinkedListItem = requires( T * t )
        {
            { t->Next( ) } -> std::convertible_to<T*>;
            { t->SetNext( t ) };
        };

        template<typename DerivedT, typename T, bool hasOwnership>
        class LinkedListBase
        {
        public:
            using DerivedType = DerivedT;
        private:
            T* head_;
            T* tail_;
        public:
            LinkedListBase( )
                : head_( nullptr ), tail_( nullptr )
            {
            }

            ~LinkedListBase( )
            {
                Clear( );
            }

            T* First( ) const
            {
                return head_;
            }
            T* Last( ) const
            {
                return tail_;
            }


            void Clear( )
            {
                if constexpr ( hasOwnership )
                {
                    auto item = head_;
                    while ( item )
                    {
                        auto tmp = item;
                        item = DerivedType::GetNext( item );
                        delete item;
                    }
                }
                head_ = nullptr;
                tail_ = nullptr;
            }

            void Add( T* item )
            {
                if ( tail_ )
                {
                    DerivedType::SetNext( tail_, item );
                    tail_ = item;
                }
                else
                {
                    head_ = item;
                    tail_ = item;
                }
            }
            bool Remove( T* itemToRemove )
            {
                if ( itemToRemove != head_ )
                {
                    T* previousItem = head_;
                    T* item = DerivedType::GetNext( head_ );
                    while ( item != itemToRemove )
                    {
                        if ( item == itemToRemove )
                        {
                            if ( item != tail_ )
                            {
                                T* nextItem = DerivedType::GetNext( item );
                                DerivedType::SetNext( previousItem, nextItem );
                            }
                            else
                            {
                                tail_ = previousItem;
                                DerivedType::SetNext( tail_, nullptr );
                            }
                            if constexpr ( hasOwnership )
                            {
                                delete itemToRemove;
                            }
                            return true;
                        }
                        previousItem = item;
                        item = DerivedType::GetNext( item );
                    }
                    return false;
                }
                else
                {
                    if ( itemToRemove != tail_ )
                    {
                        head_ = DerivedType::GetNext( itemToRemove );
                    }
                    else
                    {
                        head_ = nullptr;
                        tail_ = nullptr;
                    }
                    if constexpr ( hasOwnership )
                    {
                        delete itemToRemove;
                    }
                    return true;
                }
            }


        };

        template<typename T, bool hasOwnership>
        class LinkedList : public LinkedListBase<LinkedList<T, hasOwnership>, T, hasOwnership>
        {
            template<typename DerivedT, typename T, bool hasOwnership>
            friend class LinkedListBase;
        public:
            using Base = LinkedListBase<LinkedList<T, hasOwnership>, T, hasOwnership>;

            LinkedList( )
                : Base( )
            {
            }
        private:
            static T* GetNext( T* item )
            {
                return item->Next( );
            }
            static void SetNext( T* item, T* next )
            {
                item->SetNext( next );
            }
        };
    }



    class HttpRequestHandler;
    class HttpRequest : public Http::Request
    {
    public:
        using Base = Http::Request;
        using HttpRequestState = Internal::HttpRequestState;
        static constexpr size_t RequestDataSize = 16 * 1024;
    private:
        Byte requestData_[RequestDataSize];
        HttpRequestState requestState_;
        HttpServerRequestQueue* requestQueue_;
            
        IO::Blocks::Stream bodyStream_;
        IO::Blocks::Block* currentReceiveBodyBlock_ = nullptr;
    public:
        constexpr HttpRequest( HttpServerRequestQueue* requestQueue ) noexcept
            : Base{}, requestData_{}, requestState_( HttpRequestState::New ), requestQueue_( requestQueue ) 
        {}

        ~HttpRequest( )
        {
            if ( currentReceiveBodyBlock_ )
            {
                IO::Blocks::Block::Free( currentReceiveBodyBlock_ );
            }
        }

        HttpRequestHandler* FindHandler( const HttpRequest& request ) const;

        void Clear( )
        {
            bodyStream_.Clear( );
            if ( currentReceiveBodyBlock_ )
            {
                IO::Blocks::Block::Free( currentReceiveBodyBlock_ );
            }
        }

        constexpr HttpRequestState RequestState( ) const noexcept
        {
            return requestState_;
        }
        void SetRequestState( HttpRequestState requestState )
        {
            requestState_ = requestState;
        }
        constexpr HttpServerRequestQueue* RequestQueue( ) const noexcept
        {
            return requestQueue_;
        }

        constexpr IO::Blocks::Stream& Body( ) noexcept
        {
            return bodyStream_;
        }
        constexpr const IO::Blocks::Stream& Body( ) const noexcept
        {
            return bodyStream_;
        }
    };


    class HttpResponse : public Http::Response
    {
    public:
        using Base = Http::Response;
    private:
        HttpServerRequestQueue* requestQueue_;
        IO::Blocks::Stream bodyStream_;
    public:
        constexpr HttpResponse( HttpServerRequestQueue* requestQueue ) noexcept
            : requestQueue_( requestQueue )
        {
        }


        void Clear( )
        {

        }

        constexpr IO::Blocks::Stream& Body( ) noexcept
        {
            return bodyStream_;
        }
        constexpr const IO::Blocks::Stream& Body( ) const noexcept
        {
            return bodyStream_;
        }
    };

    class HttpRequestHandler
    {
    public:
        virtual ~HttpRequestHandler()
        { }
        virtual bool CanHandle( const HttpRequest& request ) const = 0;
        virtual void Process( const HttpRequest& request, HttpResponse& response ) = 0;
    };

    namespace Internal
    {
        class HttpReceiveRequest : public ReceiveRequest
        {
        public:
            using Base = ReceiveRequest;
        private:
            HttpRequest request_;
            HttpReceiveRequest* next_;
            HttpReceiveRequest* nextReceiving_;
        public:
            HttpReceiveRequest( HttpServerRequestQueue* requestQueue );

            ~HttpReceiveRequest( )
            {
                
            }

            void Clear( )
            {
                Base::Clear( );
                request_.Clear( );
            }


            const Http::Request& Request( ) const noexcept
            {
                return request_;
            }

            constexpr HttpRequestState RequestState( ) const noexcept
            {
                return request_.RequestState();
            }
            void SetRequestState( HttpRequestState requestState )
            {
                request_.SetRequestState( requestState );
            }
            constexpr HttpServerRequestQueue* RequestQueue( ) const noexcept
            {
                return request_.RequestQueue( );
            }

            constexpr HttpReceiveRequest* Next( ) const noexcept
            {
                return next_;
            }
            constexpr void SetNext( HttpReceiveRequest* next ) noexcept
            {
                next_ = next;
            }
            constexpr HttpReceiveRequest* NextReceiving( ) const noexcept
            {
                return nextReceiving_;
            }
            constexpr void SetNextReceiving( HttpReceiveRequest* nextReceiving ) noexcept
            {
                nextReceiving_ = nextReceiving;
            }

            constexpr IO::Blocks::Stream& Body( ) noexcept
            {
                return request_.Body( );
            }
            constexpr const IO::Blocks::Stream& Body( ) const noexcept
            {
                return request_.Body( );
            }

        };
        constexpr size_t HttpReceiveRequestSize = sizeof( HttpReceiveRequest );


        class HttpReceiveBodyRequest : public ReceiveBodyRequest
        {
        public:
            using Base = ReceiveBodyRequest;
        private:
            HttpReceiveRequest* receiveRequest_;
        public:
            HttpReceiveBodyRequest( HttpReceiveRequest* receiveRequest, IO::Blocks::Block* currentReceiveBodyBlock )
                : Base( receiveRequest->Handle( ),
                    receiveRequest->Request( ).RequestId,
                    Http::ReceiveRequestEntityBodyFlags::None,
                    currentReceiveBodyBlock->data( ),
                    IO::Blocks::Block::DataSize ), receiveRequest_( receiveRequest )
            {
            }

        };





        class HttpSendRequest : public Server::SendRequest
        {
        public:
            using Base = SendRequest;
        private:
            HttpReceiveRequest* receiveRequest_;
            Http::Response response_;
            Http::CachePolicy cachePolicy_;
            IO::Blocks::Stream bodyStream_;
        public:
            HttpSendRequest( HttpReceiveRequest* receiveRequest )
                : Base( receiveRequest->Handle( ),
                    receiveRequest->Request( ).RequestId,
                    Http::SendResponseFlags::None,
                    &response_, &cachePolicy_ ), receiveRequest_( receiveRequest )
            {
            }

            constexpr IO::Blocks::Stream& Body( ) noexcept
            {
                return bodyStream_;
            }
            constexpr const IO::Blocks::Stream& Body( ) const noexcept
            {
                return bodyStream_;
            }

        };
    }


    enum class HttpConnectionState
    {
        Unknown,
        Active,
        Disconnected
    };

    namespace Internal { class HttpConnectionManager; }

    class HttpConnection
    {
        Internal::HttpConnectionManager& connectionManager_;
        Http::ConnectionId connectionId_;
        HttpConnectionState state_;
        std::unique_ptr<WaitForDisconnectRequest> waitForDisconnectRequest_;
        boost::container::flat_map<Http::RequestId, Internal::HttpReceiveRequest*> requests_;
    public:
        HttpConnection( Internal::HttpConnectionManager& connectionManager, Http::ConnectionId connectionId, std::unique_ptr<WaitForDisconnectRequest>&& waitForDisconnectRequest )
            : connectionManager_( connectionManager ), connectionId_( connectionId ), state_( HttpConnectionState::Active ), waitForDisconnectRequest_( std::move( waitForDisconnectRequest ) )
        { }

        constexpr HttpConnectionState State( ) const noexcept
        {
            return state_;
        }

        constexpr void SetState( HttpConnectionState state ) noexcept
        {
            state_ = state;
        }

        void AddReceiveRequest( Internal::HttpReceiveRequest* request )
        {
            Http::RequestId requestId = request->Request( ).RequestId;
            requests_.emplace( requestId, request );
        }

        Internal::HttpReceiveRequest* FindReceiveRequest( Http::RequestId requestId ) const
        {
            auto it = requests_.find( requestId );
            if ( it != requests_.end( ) )
            {
                return it->second;
            }
            else
            {
                return nullptr;
            }
        }

        bool RemoveReceiveRequest( Http::RequestId requestId )
        {
            return requests_.erase( requestId ) > 0;
        }
    };
    constexpr size_t HttpConnectionSize = sizeof( HttpConnection );

    namespace Internal
    {
        class HttpConnectionManager
        {
            HttpServerRequestQueue* requestQueue_;
            boost::container::flat_map<Http::ConnectionId, std::unique_ptr<HttpConnection>> connections_;
        public:
            HttpConnectionManager( HttpServerRequestQueue* requestQueue )
                : requestQueue_( requestQueue )
            {
            }

        private:
            constexpr HANDLE Handle( ) const noexcept;
            bool BeginAsyncWaitForDisconnect( WaitForDisconnectRequest* request ) const;
        public:
            HttpConnection* AddConnection( Http::ConnectionId connectionId )
            {
                auto waitForDisconnectRequest = std::make_unique<WaitForDisconnectRequest>( Handle( ), connectionId );
                auto waitForDisconnectRequestPtr = waitForDisconnectRequest.get( );

                auto connection = std::make_unique<HttpConnection>( *this, connectionId, std::move( waitForDisconnectRequest ) );
                auto result = connection.get( );
                connections_.emplace( connectionId, std::move( connection ) );
                if ( BeginAsyncWaitForDisconnect( waitForDisconnectRequestPtr ) )
                {
                    connections_.erase( connectionId );
                }
                return result;
            }

            HttpConnection* FindConnection( Http::ConnectionId connectionId ) const
            {
                auto it = connections_.find( connectionId );
                if ( it != connections_.end( ) )
                {
                    return it->second.get( );
                }
                else
                {
                    return nullptr;
                }
            }

            bool RemoveConnection( Http::ConnectionId connectionId )
            {
                return connections_.erase( connectionId ) > 0;
            }
        };

        class HttpRequestManager
        {
        private:
            using ReceiveRequestList = Internal::LinkedList<HttpReceiveRequest, true>;
            class ReceivingRequestList : public Internal::LinkedListBase<ReceivingRequestList, HttpReceiveRequest, false>
            {
                template<typename DerivedT, typename T, bool hasOwnership>
                friend class Internal::LinkedListBase;
            public:
                using Base = Internal::LinkedListBase<ReceivingRequestList, HttpReceiveRequest, false>;
                ReceivingRequestList( )
                    : Base( )
                {
                }
            private:
                static HttpReceiveRequest* GetNext( HttpReceiveRequest* item )
                {
                    return item->NextReceiving( );
                }
                static void SetNext( HttpReceiveRequest* item, HttpReceiveRequest* next )
                {
                    item->SetNextReceiving( next );
                }
            };

            HttpServerRequestQueue* requestQueue_;
            boost::container::flat_map<Http::RequestId, HttpReceiveRequest*> activeRequests_;
            ReceiveRequestList requests_;
            ReceivingRequestList receivingRequests_;
        public:
            HttpRequestManager( HttpServerRequestQueue* requestQueue, size_t concurrentRequestCount )
                : requestQueue_( requestQueue )
            {
                for ( size_t i = 0; i < concurrentRequestCount; ++i )
                {
                    HttpReceiveRequest* newRequest = new HttpReceiveRequest( requestQueue_ );
                    requests_.Add( newRequest );
                }
            }
        private:
            constexpr HANDLE Handle( ) const noexcept;
            bool BeginAsyncReceive( ReceiveRequest* request ) const;
            bool BeginAsyncReceiveBody( ReceiveBodyRequest* request ) const;
            bool BeginAsyncSend( SendRequest* request ) const;

            HttpConnection* AddConnection( Http::ConnectionId connectionId );
            HttpConnection* FindConnection( Http::ConnectionId connectionId ) const;
            bool RemoveConnection( Http::ConnectionId connectionId );

        public:
            void AddReceiving( HttpReceiveRequest* httpRequest )
            {
                receivingRequests_.Add( httpRequest );
            }

            bool RemoveReceiving( HttpReceiveRequest* httpRequest )
            {
                return receivingRequests_.Remove( httpRequest );
            }

            void BeginReceive( HttpReceiveRequest* httpRequest )
            {
                httpRequest->SetRequestState( HttpRequestState::Receiving );
                AddReceiving( httpRequest );
                BeginAsyncReceive( httpRequest );
            }

            HttpReceiveRequest* AddRequest( )
            {
                HttpReceiveRequest* newRequest = new HttpReceiveRequest( requestQueue_ );
                requests_.Add( newRequest );
                return newRequest;
            }
            void Start( )
            {
                auto request = requests_.First( );
                while ( request )
                {
                    BeginReceive( request );
                    request = request->Next( );
                }
            }

            bool HandleReceiveCompleted( HttpReceiveRequest* request )
            {
                const Http::Request& httpRequest = request->Request( );

                request->SetRequestState( HttpRequestState::Received );

                RemoveReceiving( request );

                auto connectionId = httpRequest.ConnectionId;
                if ( connectionId != HTTP_NULL_ID )
                {
                    auto connection = FindConnection( connectionId );
                    if ( !connection )
                    {
                        connection = AddConnection( connectionId );
                    }
                    connection->AddReceiveRequest( request );

                }

                return true;
            }

        };
    }



    class HttpServerRequestQueue : public RequestQueueHandler<HttpServerRequestQueue>
    {
        template<typename DerivedT>
        friend class RequestQueueHandler;
        friend class Internal::HttpRequestManager;
    public:
        using Base = RequestQueueHandler<HttpServerRequestQueue>;
    private:
        HttpServer& server_;
        CriticalSection criticalSection_;
        size_t concurrentRequestCount_;
        Http::RequestQueue requestQueue_;
        Internal::HttpConnectionManager connectionManager_;
        Internal::HttpRequestManager requestManager_;
    protected:
        HttpServerRequestQueue( const std::shared_ptr<IO::Context>& context, HttpServer& server, size_t concurrentRequestCount, Http::RequestQueue&& requestQueue )
            : Base( context, requestQueue ), 
              server_( server ),
              concurrentRequestCount_( concurrentRequestCount ), 
              requestQueue_( std::move( requestQueue ) ),
              connectionManager_( this ),
              requestManager_( this, concurrentRequestCount )
        { 
        }
    public:
        HttpServerRequestQueue( const std::shared_ptr<IO::Context>& context, const ApiVersion& version, HttpServer& server, size_t concurrentRequestCount, const wchar_t* requestQueueName = nullptr, CreateRequestQueueFlags flags = CreateRequestQueueFlags::None, PSECURITY_ATTRIBUTES securityAttributes = nullptr)
            : HttpServerRequestQueue( context, server, concurrentRequestCount, Http::RequestQueue( version, requestQueueName, flags, securityAttributes ) )
        { 
        }

        ~HttpServerRequestQueue( )
        {
        }

        constexpr HANDLE Handle( ) const noexcept
        {
            return requestQueue_.Handle( );
        }

        HttpRequestHandler* FindHandler( const HttpRequest& request ) const;
    private:
        HttpConnection* AddConnection( Http::ConnectionId connectionId )
        {
            return connectionManager_.AddConnection( connectionId );
        }
        HttpConnection* FindConnection( Http::ConnectionId connectionId ) const
        {
            return connectionManager_.FindConnection( connectionId );
        }

        bool RemoveConnection( Http::ConnectionId connectionId )
        {
            return connectionManager_.RemoveConnection( connectionId );
        }

        void AddReceiving( Internal::HttpReceiveRequest* httpRequest )
        {
            requestManager_.AddReceiving( httpRequest );
        }

        bool RemoveReceiving( Internal::HttpReceiveRequest* httpRequest )
        {
            requestManager_.RemoveReceiving( httpRequest );
        }

        void BeginReceive( Internal::HttpReceiveRequest* httpRequest )
        {
            requestManager_.BeginReceive( httpRequest );
        }

        Internal::HttpReceiveRequest* AddRequestNL( )
        {
            return requestManager_.AddRequest( );
        }

        Internal::HttpReceiveRequest* AddRequest( )
        {
            std::unique_lock lock( criticalSection_ );
            return AddRequestNL( );
        }
    public:
        void Start( ) override
        {
            requestManager_.Start( );
        }

    private:
        bool HandleReceiveCompleted( ReceiveRequest* request )
        {
            auto* httpReceiveRequest = static_cast<Internal::HttpReceiveRequest*>( request );
            return requestManager_.HandleReceiveCompleted( httpReceiveRequest );
        }
        bool HandleReceiveBodyCompleted( ReceiveBodyRequest* request ) const
        {
            return true;
        }
        bool HandleSendCompleted( SendRequest* request ) const
        {
            return true;
        }
        bool HandleSendBodyCompleted( SendBodyRequest* request ) const
        {
            return true;
        }

        bool HandleWaitForDisconnectCompleted( WaitForDisconnectRequest* request ) const
        {
            // Find disconnected connection
            std::unique_lock lock( criticalSection_ );
            auto connectionId = request->ConnectionId( );
            auto connection = FindConnection( connectionId );
            if ( connection )
            {
                connection->SetState( HttpConnectionState::Disconnected );
                // Cancel outstanding requests

                // Reset requests

                // begin receiving new requests
            }
            return true;
        }

        bool HandleCancelCompleted( CancelRequest* request ) const
        {

            return true;
        }
    };

    inline HttpRequestHandler* HttpRequest::FindHandler( const HttpRequest& request ) const
    {
        return requestQueue_->FindHandler( request );
    }


    namespace Internal
    {
        inline HttpReceiveRequest::HttpReceiveRequest( HttpServerRequestQueue* requestQueue )
            : Base( requestQueue->Handle( ), HTTP_NULL_ID, Http::ReceiveRequestFlags::None, &request_, sizeof( HttpRequest ) ),
              request_( requestQueue ), next_( nullptr ), nextReceiving_( nullptr )
        {
        }

        inline constexpr HANDLE HttpConnectionManager::Handle( ) const noexcept
        {
            return requestQueue_->Handle( );
        }

        inline bool HttpConnectionManager::BeginAsyncWaitForDisconnect( WaitForDisconnectRequest* request ) const
        {
            return requestQueue_->BeginAsyncWaitForDisconnect( request );
        }

        inline constexpr HANDLE HttpRequestManager::Handle( ) const noexcept
        {
            return requestQueue_->Handle( );
        }

        inline bool HttpRequestManager::BeginAsyncReceive( ReceiveRequest* request ) const
        {
            return requestQueue_->BeginAsyncReceive( request );
        }

        inline bool HttpRequestManager::BeginAsyncReceiveBody( ReceiveBodyRequest* request ) const
        {
            return requestQueue_->BeginAsyncReceiveBody( request );
        }

        inline bool HttpRequestManager::BeginAsyncSend( SendRequest* request ) const
        {
            return requestQueue_->BeginAsyncSend( request );
        }

        inline HttpConnection* HttpRequestManager::AddConnection( Http::ConnectionId connectionId )
        {
            return requestQueue_->AddConnection( connectionId );
        }
        inline HttpConnection* HttpRequestManager::FindConnection( Http::ConnectionId connectionId ) const
        {
            return requestQueue_->FindConnection( connectionId );
        }
        inline bool HttpRequestManager::RemoveConnection( Http::ConnectionId connectionId )
        {
            return requestQueue_->RemoveConnection( connectionId );
        }


    }



    class HttpUrlGroup
    {
        Http::UrlGroup urlGroup_;
    public:
        HttpUrlGroup( Http::UrlGroup&& urlGroup )
            : urlGroup_(std::move( urlGroup ))
        { }

        constexpr UrlGroupId Id( ) const noexcept
        {
            return urlGroup_.Id();
        }

        void Close( ) noexcept
        {
            urlGroup_.Close( );
        }

        Http::EnabledState EnabledState( ) const
        {
            return urlGroup_.EnabledState( );
        }

        void SetEnabledState( Http::EnabledState enabledState )
        {
            urlGroup_.SetEnabledState( enabledState );
        }

        void Bind( HANDLE requestQueueHandle ) const
        {
            urlGroup_.Bind( requestQueueHandle );
        }

        void Bind( const HttpServerRequestQueue& requestQueue ) const
        {
            urlGroup_.Bind( requestQueue.RequestQueue() );
        }

        void Unbind( ) const
        {
            urlGroup_.Unbind( );
        }

        bool AddUrl( const wchar_t* fullyQualifiedUrl, Http::UrlContext urlContext = 0 ) const
        {
            return urlGroup_.AddUrl( fullyQualifiedUrl, urlContext );
        }

        bool RemoveUrl( const wchar_t* fullyQualifiedUrl ) const
        {
            return urlGroup_.RemoveUrl( fullyQualifiedUrl );
        }
        bool RemoveAllUrls( ) const
        {
            return urlGroup_.RemoveAllUrls( );
        }

    };


    class HttpServer
    {
        CriticalSection criticalSection_;
        ServerSession serverSession_;
        std::weak_ptr<IO::Context> context_;
        Http::ApiVersion version_;
        boost::container::flat_map<Http::UrlGroupId, std::unique_ptr<HttpUrlGroup>> urlGroups_;
        boost::container::flat_map<HANDLE, std::shared_ptr<HttpServerRequestQueue>> requestQueueHandlers_;
        std::deque<std::unique_ptr<HttpRequestHandler>> requestHandlers_;
    public:
        HttpServer( const std::shared_ptr<IO::Context>& context, const Http::ApiVersion& version = Http::ApiVersion( 2, 0 ) )
            : serverSession_( version ), context_( context ), version_( version )
        { }

        std::shared_ptr<IO::Context> Context( ) const
        {
            return context_.lock( );
        }


        HttpUrlGroup* AddUrlGroup()
        { 
            std::unique_lock lock( criticalSection_ );
            auto urlGroup = serverSession_.CreateUrlGroup( );
            auto httpUrlGroup = std::make_unique<HttpUrlGroup>( std::move( urlGroup ) );
            auto result = httpUrlGroup.get( );
            urlGroups_.emplace( httpUrlGroup->Id(), std::move( httpUrlGroup ) );
            return result;
        }

        std::shared_ptr<HttpServerRequestQueue> AddRequestQueue( size_t concurrentRequestCount, const wchar_t* requestQueueName = nullptr, CreateRequestQueueFlags flags = CreateRequestQueueFlags::None, PSECURITY_ATTRIBUTES securityAttributes = nullptr )
        {
            std::unique_lock lock( criticalSection_ );
            auto context = Context( );
            auto handler = std::make_shared<HttpServerRequestQueue>( context, version_, *this, concurrentRequestCount, requestQueueName, flags, securityAttributes );
            requestQueueHandlers_.emplace( handler->Handle(), handler );
            context->Bind( handler->Handle() );

            return handler;
        }


        template<typename T, typename ... Args>
        requires std::is_base_of_v< HttpRequestHandler, T>
            T* AddRequestHandler( Args&& ... args )
        {
            auto handler = std::make_unique<T>( std::forward<Args>(args)... );
            auto result = handler.get( );
            requestHandlers_.push_front( std::move( handler ) );
            return result;
        }

        HttpRequestHandler* FindHandler( const HttpRequest& request ) const
        {
            for ( auto& requestHandlerPtr : requestHandlers_ )
            {
                if ( requestHandlerPtr->CanHandle( request ) )
                {
                    return requestHandlerPtr.get( );
                }
            }
            return nullptr;
        }
    };

    inline HttpRequestHandler* HttpServerRequestQueue::FindHandler( const HttpRequest& request ) const
    {
        return server_.FindHandler( request );
    }

    class HttpRequestDispatcher : public HttpRequestHandler
    {
    public:
        boost::signals2::signal<void( const HttpRequestDispatcher& dispatcher, const HttpRequest& request, bool canHandleRequest )> OnCanHandle;
        boost::signals2::signal<void( const HttpRequestDispatcher& dispatcher, const HttpRequest& request, HttpResponse& response )> OnProcess;

        virtual bool CanHandle( const HttpRequest& request ) const final override
        {
            bool canHandleRequest = false;
            OnCanHandle(*this, request, canHandleRequest );
            return canHandleRequest;
        }
        virtual void Process( const HttpRequest& request, HttpResponse& response ) final override
        {
            OnProcess( *this, request, response );
        }

    };

}

#pragma pack(pop)

#endif
