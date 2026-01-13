#pragma once
#ifndef __HCCXML_H__
#define __HCCXML_H__
/*
   Copyright 2024-2026 Espen Harlinn

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

#include <HCCDef.h>
#include <HCCCOM.h>
#include <HCCException.h>
#include <HCCVariant.h>
#include <HCCObj.h>



namespace Harlinn::Common::Core::Xml
{
    namespace Dom
    {

        /// <summary>
        /// Provides methods that are independent of any particular 
        /// instance of the Document Object Model (DOM).
        /// </summary>
        class Implementation : public Dispatch
        {
        public:
            typedef Dispatch Base;
            HCC_COM_STANDARD_METHODS_IMPL(Implementation, Dispatch,IXMLDOMImplementation,IDispatch)

            /// <summary>
            /// Indicates support for the specified feature
            /// </summary>
            /// <param name="feature">
            /// A string that specifies the feature to test. In Level 1, valid feature 
            /// values are "XML", "DOM", and "MS-DOM" (case-insensitive).
            /// </param>
            /// <param name="version">
            /// A string that specifies the version number to test, or if Null, tests 
            /// for implementation of the feature in any version. In Level 1, "1.0" 
            /// is the valid version value.
            /// </param>
            /// <returns>
            /// Returns true if the specified feature is implemented; otherwise false.
            /// </returns>
            bool HasFeature( BSTR feature, BSTR version) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->hasFeature( feature, version, &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }
        };


        enum class NodeType
        {
            Invalid = NODE_INVALID,
            Element = NODE_ELEMENT,
            Attribute = NODE_ATTRIBUTE,
            Text = NODE_TEXT,
            CDataSection = NODE_CDATA_SECTION,
            EntityReference = NODE_ENTITY_REFERENCE,
            Entity = NODE_ENTITY,
            ProcessingInstruction = NODE_PROCESSING_INSTRUCTION,
            Comment = NODE_COMMENT,
            Document = NODE_DOCUMENT,
            DocumentType = NODE_DOCUMENT_TYPE,
            DocumentFragment = NODE_DOCUMENT_FRAGMENT,
            Notation = NODE_NOTATION
        };

        typedef SysString XmlString;

        template<typename NodeT>
        class NodeList;
        template<typename NodeT>
        class NamedNodeMap;
        class Document;

        /// <summary>
        /// Represents a single node in the XML document.
        /// </summary>
        class Node : public Dispatch
        {
        public:
            typedef Dispatch Base;
            HCC_COM_STANDARD_METHODS_IMPL(Node, Dispatch,IXMLDOMNode,IDispatch)


            void get_nodeName( BSTR* result ) const
            {
                auto pInterface = GetInterface( );
                auto hr = pInterface->get_nodeName( result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }

            /// <summary>
            /// Returns the qualified name for attribute, document type, element, 
            /// entity, or notation nodes. Returns a fixed string for all other node types.
            /// </summary>
            /// <returns>
            /// Node name, which varies depending on the node type.
            /// </returns>
            XmlString NodeName( ) const
            {
                BSTR result = 0;
                get_nodeName(&result);
                return XmlString(result,true);
            }
        
            void get_nodeValue( VARIANT* result ) const
            {
                auto pInterface = GetInterface( );
                auto hr = pInterface->get_nodeValue( result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }

            /// <summary>
            /// Retrieves the text associated with the node.
            /// </summary>
            /// <returns>
            /// Node value; depends on the NodeType property.
            /// </returns>
            Variant NodeValue( ) const
            {
                Variant result;
                get_nodeValue(&result);
                return result;
            }
        
            void SetNodeValue(const VARIANT& value) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_nodeValue(value);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }

        
            NodeType NodeType( ) const
            {
                auto pInterface = GetInterface();
                DOMNodeType result;
                auto hr = pInterface->get_nodeType(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Core::Xml::Dom::NodeType(result);
            }
        
            template<typename NodeT = Node>
            NodeT ParentNode( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_parentNode(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT = Node>
            NodeList<NodeT> ChildNodes( ) const;
        
            template<typename NodeT = Node>
            NodeT FirstChild( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_firstChild(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT = Node>
            NodeT LastChild( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_lastChild(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT = Node>
            NodeT PreviousSibling( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_previousSibling(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT = Node>
            NodeT NextSibling( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_nextSibling(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT = Node>
            NamedNodeMap<NodeT> Attributes() const;
        
            template<typename NodeT = Node>
            NodeT InsertBefore( IXMLDOMNode *newChild,const VARIANT& refChild) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->insertBefore( newChild, refChild,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT = Node>
            NodeT ReplaceChild( IXMLDOMNode *newChild,IXMLDOMNode *oldChild) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->replaceChild( newChild, oldChild,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT = Node>
            NodeT RemoveChild( IXMLDOMNode *childNode ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->removeChild( childNode,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT = Node>
            NodeT AppendChild( IXMLDOMNode *newChild ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->appendChild( newChild,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }

            bool HasChildNodes( ) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->hasChildNodes( &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }
        
            Document OwnerDocument( ) const;
        
            template<typename NodeT = Node>
            NodeT CloneNode( bool deep = true) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->cloneNode( deep?VARIANT_TRUE:VARIANT_FALSE,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            XmlString NodeTypeString( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_nodeTypeString(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            XmlString Text( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_text(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            void SetText( BSTR text) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_text(text);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }

            void SetText( const wchar_t* text ) const
            {
                SetText( ( BSTR )text );
            }

            void SetText( const XmlString& text ) const
            {
                SetText( text.c_str( ) );
            }

            
            void SetText( const WideString& text ) const
            {
                SetText( text.c_str() );
            }
            void SetText( const AnsiString& text ) const
            {
                XmlString xmlString( text );
                SetText( xmlString );
            }

        
            bool Specified( ) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->get_specified( &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }
        
            template<typename NodeT = Node>
            NodeT Definition( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_definition( &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            Variant NodeTypedValue( ) const
            {
                auto pInterface = GetInterface();
                Variant result;
                auto hr = pInterface->get_nodeTypedValue( &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
        
            void SetNodeTypedValue( const VARIANT& typedValue ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_nodeTypedValue( typedValue );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            Variant DataType( ) const
            {
                auto pInterface = GetInterface();
                Variant result;
                auto hr = pInterface->get_dataType( &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }

            void SetDataType( BSTR dataTypeName ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_dataType(dataTypeName);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            XmlString Xml( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_xml(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            XmlString TransformNode( IXMLDOMNode *stylesheet) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->transformNode(stylesheet, &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            template<typename NodeT = Node>
            NodeList<NodeT> SelectNodes( BSTR queryString ) const;

            template<typename NodeT = Node>
            NodeList<NodeT> SelectNodes( const wchar_t* queryString ) const
            {
                return SelectNodes<NodeT>( (BSTR)queryString );
            }
            template<typename NodeT = Node>
            NodeList<NodeT> SelectNodes( const WideString& queryString ) const
            {
                return SelectNodes<NodeT>( ( BSTR )queryString.c_str() );
            }


            template<typename NodeT = Node>
            NodeT SelectSingleNode( BSTR queryString ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->selectSingleNode( queryString,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            bool Parsed( ) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->get_parsed( &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }
        
            XmlString NamespaceURI( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_namespaceURI(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            XmlString Prefix( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_prefix(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            XmlString BaseName( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_baseName(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            void TransformNodeToObject( IXMLDOMNode *stylesheet, IXMLDOMDocument* outputObject) const
            {
                auto pInterface = GetInterface();
                Variant destination(outputObject);
                auto hr = pInterface->transformNodeToObject( stylesheet, destination);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }

            void TransformNodeToObject( IXMLDOMNode *stylesheet, IStream* outputObject) const
            {
                auto pInterface = GetInterface();
                Variant destination(outputObject);
                auto hr = pInterface->transformNodeToObject( stylesheet, destination);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        };

        template<typename NCT, typename NodeT>
        class NodeIterator
        {
        public:
            using CollectionType = NCT;
            using NodeType = NodeT;
            using iterator_category = std::random_access_iterator_tag;
            using value_type = NodeT;
            using difference_type = SSIZE_T;
            using pointer = const value_type*;
            using reference = const value_type&;
        private:
            CollectionType* collection_;
            size_t index_;
            size_t size_;
            NodeType node_;
        public:
            explicit NodeIterator( )
                : collection_( nullptr ), index_( 0 ), size_( 0 )
            {
            }

            explicit NodeIterator( CollectionType* collection )
                : collection_( collection ), index_(0), size_(0)
            {
                if ( collection_ )
                {
                    size_ = collection_->size( );
                    if ( size_ )
                    {
                        node_ = collection_->Item( static_cast< long >( 0 ) );
                    }
                }
            }

            explicit NodeIterator( CollectionType* collection, bool end )
                : collection_( collection ), index_( 0 ), size_( 0 )
            {
                if ( collection_ )
                {
                    size_ = collection_->size( );
                    index_ = size_;
                }
            }

            reference operator*( ) const
            {
                return node_;
            }
            pointer operator->( ) const
            {
                return &node_;
            }

            NodeIterator& operator++( )
            {
                ++index_;
                node_ = collection_->Item( static_cast<long>( index_ ) );
                return *this;
            }

            NodeIterator operator++( int )
            {
                auto tmp = *this;
                ++*this;
                return tmp;
            }
            NodeIterator& operator--( )
            {
                --index_;
                node_ = collection_->Item( static_cast<long>( index_ ) );
                return *this;
            }

            NodeIterator operator--( int )
            {
                auto tmp = *this;
                --* this;
                return tmp;
            }

            NodeIterator& operator += ( const difference_type offset )
            {
                index_ += static_cast<size_t>( offset );
                node_ = collection_->Item( static_cast<long>( index_ ) );
                return *this;
            }

            [[nodiscard]] NodeIterator operator+( const difference_type offset ) const
            {
                NodeIterator tmp = *this;
                tmp += offset;
                return tmp;
            }

            NodeIterator& operator-=( const difference_type offset )
            {
                index_ -= static_cast<size_t>( offset );
                node_ = collection_->Item( static_cast<long>( index_ ) );
                return *this;
            }

            [[nodiscard]] NodeIterator operator-( const difference_type offset ) const
            {
                NodeIterator tmp = *this;
                tmp -= offset;
                return tmp;
            }

            constexpr bool operator == ( const NodeIterator& other ) const noexcept
            {
                return index_ == other.index_;
            }
            constexpr bool operator != ( const NodeIterator& other ) const noexcept
            {
                return index_ != other.index_;
            }
            constexpr bool operator < ( const NodeIterator& other ) const noexcept
            {
                return index_ < other.index_;
            }
            constexpr bool operator <= ( const NodeIterator& other ) const noexcept
            {
                return index_ <= other.index_;
            }
            constexpr bool operator > ( const NodeIterator& other ) const noexcept
            {
                return index_ > other.index_;
            }
            constexpr bool operator >= ( const NodeIterator& other ) const noexcept
            {
                return index_ >= other.index_;
            }
        };

        template<typename NodeT = Node>
        class NodeList : public Dispatch
        {
        public:
            using NodeType = NodeT;
            using value_type = NodeType;
            using const_iterator = NodeIterator<const NodeList<NodeType>, const NodeType>;
            using iterator = NodeIterator<NodeList<NodeType>, NodeType>;
            using reverse_iterator = std::reverse_iterator<iterator>;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;

            typedef Dispatch Base;
            HCC_COM_STANDARD_METHODS_IMPL(NodeList, Dispatch,IXMLDOMNodeList,IDispatch)

            [[nodiscard]] iterator begin( )
            {
                return iterator( this );
            }
            [[nodiscard]] iterator end( )
            {
                return iterator( this, true );
            }
            [[nodiscard]] const_iterator begin( ) const
            {
                return const_iterator( this );
            }
            [[nodiscard]] const_iterator end( ) const
            {
                return const_iterator( this, true );
            }
            [[nodiscard]] const_iterator cbegin( ) const
            {
                return const_iterator( this );
            }
            [[nodiscard]] const_iterator cend( ) const
            {
                return const_iterator( this, true );
            }

            [[nodiscard]] [[nodiscard]] reverse_iterator rbegin( ) noexcept
            {
                return reverse_iterator( end( ) );
            }

            [[nodiscard]] const_reverse_iterator rbegin( ) const noexcept
            {
                return const_reverse_iterator( end( ) );
            }

            [[nodiscard]] reverse_iterator rend( ) noexcept
            {
                return reverse_iterator( begin( ) );
            }

            [[nodiscard]] const_reverse_iterator rend( ) const noexcept
            {
                return const_reverse_iterator( begin( ) );
            }

            template<typename NodeT2 = NodeType>
            NodeT2 Item( long index ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_item(index,&result);
                if ( hr != S_FALSE )
                {
                    HCC_COM_CHECK_HRESULT2( hr, pInterface );
                    if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT2>, Node> )
                    {
                        return NodeT2( result );
                    }
                    else
                    {
                        using InterfaceType = typename NodeT::InterfaceType;
                        InterfaceType* pNodeType = nullptr;
                        hr = result->QueryInterface<InterfaceType>( &pNodeType );
                        HCC_COM_CHECK_HRESULT2( hr, result );
                        NodeT2 node( pNodeType );
                        result->Release( );
                        return node;
                    }
                }
                return {};
            }
        
            long Length( ) const
            {
                if(unknown_)
                {
                    auto pInterface = GetInterface();
                    long result = 0;
                    auto hr = pInterface->get_length(&result);
                    HCC_COM_CHECK_HRESULT2( hr, pInterface );
                    return result;
                }
                return 0;
            }

            size_t size( ) const
            {
                return static_cast<size_t>( Length( ) );
            }

            NodeType operator[]( size_t index ) const
            {
                return Item( static_cast<long>( index ) );
            }


            template<typename NodeT2 = NodeType>
            NodeT2 NextNode( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->nextNode(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT2>, Node> )
                {
                    return NodeT2( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT2 node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            void Reset( void ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->reset( );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            EnumUnknown NewEnum( ) const
            {
                auto pInterface = GetInterface();
                IUnknown *pUnknown = nullptr;
                auto hr = pInterface->get__newEnum(&pUnknown);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                IEnumUnknown* pEnum = nullptr;

                hr = pUnknown->QueryInterface<IEnumUnknown>(&pEnum);
                pUnknown->Release();
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return EnumUnknown(pEnum);
            }
        
        };

        template<typename NodeT>
        inline NodeList<NodeT> Node::ChildNodes( ) const
        {
            auto pInterface = GetInterface();
            IXMLDOMNodeList *result = nullptr;
            auto hr = pInterface->get_childNodes(&result);
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return NodeList<NodeT>(result);
        }

        template<typename NodeT>
        inline NodeList<NodeT> Node::SelectNodes( BSTR queryString ) const
        {
            auto pInterface = GetInterface();
            IXMLDOMNodeList *result;
            auto hr = pInterface->selectNodes(queryString, &result);
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return NodeList<NodeT>(result);
        }

        template<typename NodeT = Node>
        class NamedNodeMap : public Dispatch
        {
        public:
            using NodeType = NodeT;
            using value_type = NodeT;
            using const_iterator = NodeIterator<const NamedNodeMap, const Node>;
            using iterator = NodeIterator<NamedNodeMap, Node>;
            using reverse_iterator = std::reverse_iterator<iterator>;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;

            typedef Dispatch Base;
            HCC_COM_STANDARD_METHODS_IMPL(NamedNodeMap, Dispatch,IXMLDOMNamedNodeMap,IDispatch)


            [[nodiscard]] iterator begin( )
            {
                return iterator( this );
            }
            [[nodiscard]] iterator end( )
            {
                return iterator( this, true );
            }
            [[nodiscard]] const_iterator begin( ) const
            {
                return const_iterator( this );
            }
            [[nodiscard]] const_iterator end( ) const
            {
                return const_iterator( this, true );
            }
            [[nodiscard]] const_iterator cbegin( ) const
            {
                return const_iterator( this );
            }
            [[nodiscard]] const_iterator cend( ) const
            {
                return const_iterator( this, true );
            }

            [[nodiscard]] [[nodiscard]] reverse_iterator rbegin( ) noexcept
            {
                return reverse_iterator( end( ) );
            }

            [[nodiscard]] const_reverse_iterator rbegin( ) const noexcept
            {
                return const_reverse_iterator( end( ) );
            }

            [[nodiscard]] reverse_iterator rend( ) noexcept
            {
                return reverse_iterator( begin( ) );
            }

            [[nodiscard]] const_reverse_iterator rend( ) const noexcept
            {
                return const_reverse_iterator( begin( ) );
            }

            template<typename NodeT2 = NodeType>
            NodeT2 NamedItem( BSTR name ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->getNamedItem(name,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT2>, Node> )
                {
                    return NodeT2( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT2 node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT2 = NodeType>
            NodeT2 SetNamedItem( IXMLDOMNode *newItem) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->setNamedItem(newItem,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT2>, Node> )
                {
                    return NodeT2( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT2 node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT2 = NodeType>
            NodeT2 RemoveNamedItem( BSTR name ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->removeNamedItem(name,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT2>, Node> )
                {
                    return NodeT2( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT2 node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            template<typename NodeT2 = NodeType>
            NodeT2 Item( long index ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_item(index,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT2>, Node> )
                {
                    return NodeT2( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT2 node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            long Length( ) const
            {
                if( unknown_ )
                {
                    auto pInterface = GetInterface();
                    long result = 0;
                    auto hr = pInterface->get_length(&result);
                    HCC_COM_CHECK_HRESULT2( hr, pInterface );
                    return result;
                }
                return 0;
            }

            size_t size( ) const
            {
                return static_cast<size_t>( Length( ) );
            }

            NodeType operator[]( size_t index ) const
            {
                return Item( static_cast<long>( index ) );
            }

        
            template<typename NodeT2 = NodeType>
            NodeT2 QualifiedItem( BSTR baseName,BSTR namespaceURI) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->getQualifiedItem(baseName,namespaceURI,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT2>, Node> )
                {
                    return NodeT2( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT2 node( pNodeType );
                    result->Release( );
                    return node;
                }
            }

            template<typename NodeT2 = NodeType>
            NodeT2 RemoveQualifiedItem( BSTR baseName,BSTR namespaceURI) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->removeQualifiedItem(baseName,namespaceURI,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT2>, Node> )
                {
                    return NodeT2( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT2 node( pNodeType );
                    result->Release( );
                    return node;
                }
            }

            template<typename NodeT2 = NodeType>
            NodeT2 NextNode( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->nextNode(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT2>, Node> )
                {
                    return NodeT2( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT2 node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            void Reset( void ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->reset( );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            EnumUnknown NewEnum( ) const
            {
                auto pInterface = GetInterface();
                IUnknown *pUnknown = nullptr;
                auto hr = pInterface->get__newEnum(&pUnknown);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                IEnumUnknown* pEnum = nullptr;

                hr = pUnknown->QueryInterface<IEnumUnknown>(&pEnum);
                pUnknown->Release();
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return EnumUnknown(pEnum);
            }
        
        };

        template<typename NodeT>
        inline NamedNodeMap<NodeT> Node::Attributes() const
        {
            auto pInterface = GetInterface();
            IXMLDOMNamedNodeMap *result = nullptr;
            auto hr = pInterface->get_attributes(&result);
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return NamedNodeMap<NodeT>(result);
        }


        class DocumentType : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL(DocumentType, Node,IXMLDOMDocumentType,IXMLDOMNode)

            XmlString Name( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_name(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            template<typename NodeT = Node>
            NamedNodeMap<NodeT> Entities( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNamedNodeMap *result = nullptr;
                auto hr = pInterface->get_entities(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return NamedNodeMap<NodeT>(result);
            }
        
            template<typename NodeT = Node>
            NamedNodeMap<NodeT> get_notations( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNamedNodeMap *result = nullptr;
                auto hr = pInterface->get_notations(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return NamedNodeMap<NodeT>(result);
            }
        };

        class Notation : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL( Notation, Node, IXMLDOMNotation, IXMLDOMNode )

            Variant PublicId( ) const
            {
                auto pInterface = GetInterface( );
                Variant result;
                auto hr = pInterface->get_publicId( &result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }

            Variant SystemId( ) const
            {
                auto pInterface = GetInterface( );
                Variant result;
                auto hr = pInterface->get_systemId( &result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
        };

        class Entity : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL( Entity, Node, IXMLDOMEntity, IXMLDOMNode )

                Variant PublicId( ) const
            {
                auto pInterface = GetInterface( );
                Variant result;
                auto hr = pInterface->get_publicId( &result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }

            Variant SystemId( ) const
            {
                auto pInterface = GetInterface( );
                Variant result;
                auto hr = pInterface->get_systemId( &result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }

            XmlString NotationName( ) const
            {
                auto pInterface = GetInterface( );
                BSTR result = nullptr;
                auto hr = pInterface->get_notationName( &result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString( result, true );
            }

        };




        class Attribute : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL(Attribute, Node,IXMLDOMAttribute,IXMLDOMNode)

            XmlString Name( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_name(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            Variant Value( ) const
            {
                auto pInterface = GetInterface();
                Variant result;
                auto hr = pInterface->get_value( &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
        
            void SetValue( const VARIANT& attributeValue ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_value( attributeValue );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        };


        class Element : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL(Element, Node,IXMLDOMElement,IXMLDOMNode)

            XmlString TagName( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_tagName(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            Variant Attribute(const wchar_t* name) const
            {
                auto pInterface = GetInterface();
                Variant result;
                auto hr = pInterface->getAttribute((BSTR)name, &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
            Variant Attribute( const WideString& name ) const
            {
                return Attribute( name.c_str() );
            }
            Variant Attribute( const XmlString& name ) const
            {
                return Attribute( name.c_str( ) );
            }

            bool TryGetAttribute( const wchar_t* name, Variant& result ) const
            {
                auto pInterface = GetInterface( );
                auto hr = pInterface->getAttribute( ( BSTR )name, &result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return hr == S_OK;
            }

            bool TryGetAttribute( const WideString& name, Variant& result ) const
            {
                return TryGetAttribute( name.c_str( ), result );
            }

            bool TryGetAttribute( const XmlString& name, Variant& result ) const
            {
                return TryGetAttribute( name.c_str( ), result );
            }


            bool HasAttribute( const wchar_t* name ) const
            {
                auto pInterface = GetInterface( );
                Variant value;
                auto hr = pInterface->getAttribute( ( BSTR )name, &value );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return hr == S_OK;
            }
            template<SimpleWideStringLike StringT>
            bool HasAttribute( const StringT& name ) const
            {
                return HasAttribute( name.c_str() );
            }
        
            void SetAttribute( BSTR name,VARIANT value) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->setAttribute( name, value );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            void RemoveAttribute( BSTR name) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->removeAttribute( name );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            Core::Xml::Dom::Attribute AttributeNode(BSTR name) const
            {
                auto pInterface = GetInterface();
                IXMLDOMAttribute *result = nullptr;
                auto hr = pInterface->getAttributeNode(name,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Core::Xml::Dom::Attribute(result);
            }
            Core::Xml::Dom::Attribute AttributeNode( const wchar_t* name ) const
            {
                return AttributeNode( (BSTR)name );
            }
        
            Core::Xml::Dom::Attribute SetAttributeNode(IXMLDOMAttribute *DOMAttribute) const
            {
                auto pInterface = GetInterface();
                IXMLDOMAttribute *result = nullptr;
                auto hr = pInterface->setAttributeNode(DOMAttribute,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Core::Xml::Dom::Attribute(result);
            }
        
            Core::Xml::Dom::Attribute RemoveAttributeNode(IXMLDOMAttribute *DOMAttribute) const
            {
                auto pInterface = GetInterface();
                IXMLDOMAttribute *result = nullptr;
                auto hr = pInterface->removeAttributeNode(DOMAttribute,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Core::Xml::Dom::Attribute(result);
            }

            template<typename ElementT = Element>
            NodeList<ElementT> ElementsByTagName( BSTR tagName ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNodeList *result = nullptr;
                auto hr = pInterface->getElementsByTagName(tagName,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return NodeList<ElementT>(result);
            }

            template<typename ElementT = Element>
            NodeList<ElementT> ElementsByTagName( const wchar_t* tagName ) const
            {
                return ElementsByTagName<ElementT>( (BSTR)tagName );
            }

            Element FindElement( BSTR tagName ) const
            {
                auto pInterface = GetInterface( );
                IXMLDOMNodeList* domNodeList = nullptr;
                auto hr = pInterface->getElementsByTagName( tagName, &domNodeList );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                NodeList nodeList( domNodeList );
                auto size = nodeList.Length( );
                if ( size )
                {
                    auto item = nodeList.Item( 0 );
                    return item.As<Element>( );
                }
                else
                {
                    return Element( );
                }
            }

            Element FindElement( const wchar_t* tagName ) const
            {
                return FindElement( (BSTR)tagName );
            }

            template<SimpleWideStringLike StringT>
            Element FindElement( const StringT& tagName ) const
            {
                return FindElement( tagName.c_str() );
            }

        
            void Normalize( ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->normalize( );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }


            template<typename T>
                requires (std::is_arithmetic_v<T> || std::is_same_v<T,DateTime> || std::is_same_v<T, TimeSpan> || 
                    std::is_same_v<T, WideString> || std::is_same_v<T, AnsiString> || std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring> || std::is_same_v<T, SysString> ||
                        std::is_same_v<T, Guid> || std::is_same_v<T, Currency> )
            T Read(const wchar_t* attributeName ) const
            { 
                Variant variant;
                if ( TryGetAttribute( attributeName, variant ) )
                {
                    return variant.As<T>( );
                }
                return {};
            }

            template<typename T, SimpleWideStringLike StringT>
                requires (std::is_arithmetic_v<T> || std::is_same_v<T,DateTime> || std::is_same_v<T, TimeSpan> || 
                    std::is_same_v<T, WideString> || std::is_same_v<T, AnsiString> || std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring> || std::is_same_v<T, SysString> ||
                        std::is_same_v<T, Guid> || std::is_same_v<T, Currency> )
            T Read(const StringT& attributeName ) const
            { 
                Variant variant;
                if ( TryGetAttribute( attributeName.c_str(), variant ) )
                {
                    return variant.As<T>( );
                }
                return {};
            }

            template<typename T>
                requires (std::is_arithmetic_v<T> || std::is_same_v<T,DateTime> || std::is_same_v<T, TimeSpan> || 
                    std::is_same_v<T, WideString> || std::is_same_v<T, AnsiString> || std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring> || std::is_same_v<T, SysString> ||
                        std::is_same_v<T, Guid> || std::is_same_v<T, Currency> )
            T Read(const wchar_t* attributeName, const T& defaultValue ) const
            { 
                Variant variant;
                if ( TryGetAttribute( attributeName, variant ) )
                {
                    return variant.As<T>( );
                }
                return defaultValue;
            }

            template<typename T, SimpleWideStringLike StringT>
                requires (std::is_arithmetic_v<T> || std::is_same_v<T,DateTime> || std::is_same_v<T, TimeSpan> || 
                    std::is_same_v<T, WideString> || std::is_same_v<T, AnsiString> || std::is_same_v<T, std::string> || std::is_same_v<T, std::wstring> || std::is_same_v<T, SysString> ||
                        std::is_same_v<T, Guid> || std::is_same_v<T, Currency> )
            T Read(const StringT& attributeName, const T& defaultValue ) const
            { 
                Variant variant;
                if ( TryGetAttribute( attributeName.c_str(), variant ) )
                {
                    return variant.As<T>( );
                }
                return defaultValue;
            }

            template<typename T>
                requires ( IsStdOptional<T> && 
                    (std::is_arithmetic_v<typename T::value_type> || std::is_same_v<typename T::value_type,DateTime> || std::is_same_v<typename T::value_type, TimeSpan> ||
                    std::is_same_v<typename T::value_type, WideString> || std::is_same_v<typename T::value_type, AnsiString> || std::is_same_v<typename T::value_type, std::string> || std::is_same_v<typename T::value_type, std::wstring> || std::is_same_v<typename T::value_type, SysString> ||
                        std::is_same_v<typename T::value_type, Guid> || std::is_same_v<typename T::value_type, Currency> ) )
            T Read(const wchar_t* attributeName ) const
            { 
                Variant variant;
                if ( TryGetAttribute( attributeName, variant ) )
                {
                    return variant.As<typename T::value_type>( );
                }
                return {};
            }

            template<typename T, SimpleWideStringLike StringT>
                requires ( IsStdOptional<T> && 
                    (std::is_arithmetic_v<typename T::value_type> || std::is_same_v<typename T::value_type,DateTime> || std::is_same_v<typename T::value_type, TimeSpan> ||
                    std::is_same_v<typename T::value_type, WideString> || std::is_same_v<typename T::value_type, AnsiString> || std::is_same_v<typename T::value_type, std::string> || std::is_same_v<typename T::value_type, std::wstring> || std::is_same_v<typename T::value_type, SysString> ||
                        std::is_same_v<typename T::value_type, Guid> || std::is_same_v<typename T::value_type, Currency> ) )
            T Read(const StringT& attributeName ) const
            { 
                Variant variant;
                if ( TryGetAttribute( attributeName.c_str(), variant ) )
                {
                    return variant.As<typename T::value_type>( );
                }
                return {};
            }

            
            template<typename T>
                requires std::is_enum_v<T> &&
                requires( T& value, const WideString& str)
                { 
                    { TryParse( str, value ) } -> std::same_as<bool>;
                }
            T Read( const wchar_t* attributeName ) const
            {
                Variant variant;
                if ( TryGetAttribute( attributeName, variant ) )
                {
                    auto str = variant.As<WideString>( );
                    T value;
                    if ( TryParse( str, value ) )
                    {
                        return value;
                    }
                }
                throw ArgumentException( L"attributeName" );
            }
            

            template<typename T, SimpleWideStringLike StringT>
                requires std::is_enum_v<T>&&
                requires( T& value, const WideString& str )
                {
                    { TryParse( str, value ) } -> std::same_as<bool>;
                }
            T Read( const StringT& attributeName ) const
            {
                Variant variant;
                if ( TryGetAttribute( attributeName.c_str(), variant ) )
                {
                    auto str = variant.As<StringT>( );
                    T value;
                    if ( TryParse( str, value ) )
                    {
                        return value;
                    }
                }
                throw ArgumentException( L"attributeName" );
            }


            template<typename T>
                requires (IsStdOptional<T> && std::is_enum_v<typename T::value_type>) &&
                requires( typename T::value_type& value, const WideString& str)
                { 
                    { TryParse( str, value ) } -> std::same_as<bool>;
                }
            T Read( const wchar_t* attributeName ) const
            {
                Variant variant;
                if ( TryGetAttribute( attributeName, variant ) )
                {
                    auto str = variant.As<WideString>( );
                    typename T::value_type value;
                    if ( TryParse( str, value ) )
                    {
                        return value;
                    }
                }
                return {};
            }

            template<typename T, SimpleWideStringLike StringT>
                requires ( IsStdOptional<T>&& std::is_enum_v<typename T::value_type> ) &&
                requires( typename T::value_type& value, const WideString& str )
                {
                    { TryParse( str, value ) } -> std::same_as<bool>;
                }
            T Read( const StringT& attributeName ) const
            {
                Variant variant;
                if ( TryGetAttribute( attributeName, variant ) )
                {
                    auto str = variant.As<WideString>( );
                    typename T::value_type value;
                    if ( TryParse( str, value ) )
                    {
                        return value;
                    }
                }
                return {};
            }

            template<typename T>
                requires std::is_same_v<T,Element>
            T Read( const wchar_t* tagName ) const
            {
                auto childNodes = ChildNodes( );
                for ( const auto& childNode : childNodes )
                {
                    auto nodeType = childNode.NodeType( );
                    if ( nodeType == Dom::NodeType::Element )
                    {
                        auto element = childNode.As<Element>( );
                        auto elementTagName = element.TagName( );
                        if ( elementTagName == tagName )
                        {
                            return element;
                        }
                    }
                }
                return {};
            }

            template<typename T, SimpleWideStringLike StringT>
                requires std::is_same_v<T, Element>
            T Read( const StringT& tagName ) const
            {
                return Read<Element>( tagName.c_str() );
            }

        };

        


        class DocumentFragment : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL(DocumentFragment, Node,IXMLDOMDocumentFragment,IXMLDOMNode)
        };

        class CharacterData : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL(CharacterData, Node,IXMLDOMCharacterData,IXMLDOMNode)

            XmlString Data( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_data(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            void SetData( BSTR data ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_data(data);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            long Length( ) const
            {
                auto pInterface = GetInterface();
                long result = 0;
                auto hr = pInterface->get_length(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
        
            XmlString SubstringData( long offset,long count,BSTR *data ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->substringData(offset,count,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            void AppendData( BSTR data ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->appendData(data);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
            void InsertData( long offset, BSTR data) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->insertData(offset, data);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            void DeleteData( long offset,long count) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->deleteData(offset, count );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }

            void ReplaceData( long offset,long count, BSTR data) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->replaceData(offset, count, data);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
        };


        class Text : public CharacterData
        {
        public:
            typedef CharacterData Base;
            HCC_COM_STANDARD_METHODS_IMPL(Text, CharacterData,IXMLDOMText,IXMLDOMCharacterData)

            Text splitText( long offset ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMText *result = nullptr;
                auto hr = pInterface->splitText(offset,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Text(result);
            }
        };

        class Comment : public CharacterData
        {
        public:
            typedef CharacterData Base;
            HCC_COM_STANDARD_METHODS_IMPL(Comment, CharacterData,IXMLDOMComment,IXMLDOMCharacterData)

        };



        class CDATASection : public Text
        {

        public:
            typedef Text Base;
            HCC_COM_STANDARD_METHODS_IMPL(CDATASection,Text,IXMLDOMCDATASection ,IXMLDOMText)
        };


        class ProcessingInstruction : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL(ProcessingInstruction, Node,IXMLDOMProcessingInstruction,IXMLDOMNode)

            XmlString Target( BSTR *name ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_target(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }

            XmlString Data( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_data(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            void SetData( BSTR data ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_data(data);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
        };


        class EntityReference : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL(EntityReference, Node,IXMLDOMEntityReference,IXMLDOMNode)
        };


        class ParseError : public Dispatch
        {
        public:
            typedef Dispatch Base;
            HCC_COM_STANDARD_METHODS_IMPL(ParseError, Dispatch,IXMLDOMParseError,IDispatch)

            long ErrorCode( ) const
            {
                auto pInterface = GetInterface();
                long result = 0;
                auto hr = pInterface->get_errorCode(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
        
            XmlString Url( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_url(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            XmlString Reason( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_reason(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            XmlString SrcText( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_srcText(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            long Line( ) const
            {
                auto pInterface = GetInterface();
                long result = 0;
                auto hr = pInterface->get_line(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
        
            long LinePos( ) const
            {
                auto pInterface = GetInterface();
                long result = 0;
                auto hr = pInterface->get_linepos(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
        
            long FilePos() const
            {
                auto pInterface = GetInterface();
                long result = 0;
                auto hr = pInterface->get_filepos(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
        
        };

        class ParseErrorCollection;
        class ParseError2 : public ParseError
        {
        public:
            using Base = ParseError;
            HCC_COM_STANDARD_METHODS_IMPL( ParseError2, ParseError, IXMLDOMParseError2, IXMLDOMParseError )

            XmlString ErrorXPath( ) const
            {
                auto pInterface = GetInterface( );
                BSTR result = 0;
                auto hr = pInterface->get_errorXPath( &result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString( result, true );
            }

            inline ParseErrorCollection AllErrors( ) const;

            XmlString ErrorParameters( size_t index ) const
            {
                auto pInterface = GetInterface( );
                BSTR result = 0;
                auto hr = pInterface->errorParameters( static_cast<long>( index ), &result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString( result, true );
            }

            size_t ErrorParametersCount( ) const
            {
                auto pInterface = GetInterface( );
                long result = 0;
                auto hr = pInterface->get_errorParametersCount( &result );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return static_cast<size_t>( result );
            }


        };


        class ParseErrorCollection : public Dispatch
        {
        public:
            typedef Dispatch Base;
            HCC_COM_STANDARD_METHODS_IMPL( ParseErrorCollection, Dispatch, IXMLDOMParseErrorCollection, IDispatch )

                
        };

        inline ParseErrorCollection ParseError2::AllErrors( ) const
        {
            auto pInterface = GetInterface( );
            IXMLDOMParseErrorCollection* result = nullptr;
            auto hr = pInterface->get_allErrors( &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return ParseErrorCollection( result );
        }
        


        class SchemaCollection : public Dispatch
        {
        public:
            typedef Dispatch Base;
            HCC_COM_STANDARD_METHODS_IMPL(SchemaCollection, Dispatch,IXMLDOMSchemaCollection,IDispatch)

            void Add( BSTR namespaceURI, const VARIANT& var) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->add(namespaceURI, var);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            Node SchemaNodeForNamespace( BSTR namespaceURI ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode* result = 0;
                auto hr = pInterface->get(namespaceURI,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            void Remove( BSTR namespaceURI) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->remove(namespaceURI);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            long Length( ) const
            {
                auto pInterface = GetInterface();
                long result = 0;
                auto hr = pInterface->get_length(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }

            XmlString At( long index ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_namespaceURI(index,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            XmlString NamespaceURI( long index ) const
            {
                auto pInterface = GetInterface();
                BSTR result = 0;
                auto hr = pInterface->get_namespaceURI(index,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            void AddCollection( IXMLDOMSchemaCollection *otherCollection) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->addCollection(otherCollection);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            EnumUnknown NewEnum( ) const
            {
                auto pInterface = GetInterface();
                IUnknown *pUnknown = nullptr;
                auto hr = pInterface->get__newEnum(&pUnknown);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                IEnumUnknown* pEnum = nullptr;

                hr = pUnknown->QueryInterface<IEnumUnknown>(&pEnum);
                pUnknown->Release();
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return EnumUnknown(pEnum);
            }
        
        };




        class Document : public Node
        {
        public:
            typedef Node Base;
            HCC_COM_STANDARD_METHODS_IMPL(Document, Node,IXMLDOMDocument3,IXMLDOMNode)

            explicit Document( bool freeThreaded, const wchar_t* xml, bool validateOnParse = false, bool resolveExternals = false, bool preserveWhiteSpace = false, bool async = false )
            {
                IXMLDOMDocument3* pInterface = nullptr;
                HRESULT hr = 0;
                if ( freeThreaded )
                {
                    hr = CoCreateInstance( __uuidof( FreeThreadedDOMDocument60 ), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &pInterface ) );
                }
                else
                {
                    hr = CoCreateInstance( __uuidof( DOMDocument60 ), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &pInterface ) );
                }
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                ResetPtr( pInterface );
                SetValidateOnParse( validateOnParse );
                SetResolveExternals( resolveExternals );
                SetPreserveWhiteSpace( preserveWhiteSpace );
                SetAsync( async );
                LoadXML( xml );
            }

            explicit Document( const wchar_t* xml, bool validateOnParse = false, bool resolveExternals = false, bool preserveWhiteSpace = false, bool async = false )
                : Document( false, xml, validateOnParse, resolveExternals, preserveWhiteSpace, async )
            {
            }


            template<WideStringLike StringT>
            explicit Document( const StringT& xml, bool validateOnParse = false, bool resolveExternals = false, bool preserveWhiteSpace = false, bool async = false )
                : Document( xml.c_str(), validateOnParse, resolveExternals, preserveWhiteSpace, async )
            {
            }

            template<WideStringLike StringT>
            explicit Document( bool freeThreaded, const StringT& xml, bool validateOnParse = false, bool resolveExternals = false, bool preserveWhiteSpace = false, bool async = false )
                : Document( freeThreaded, xml.c_str( ), validateOnParse, resolveExternals, preserveWhiteSpace, async )
            {
            }

            static Document Create( bool freeThreaded = false )
            {
                IXMLDOMDocument3* pInterface = nullptr;
                HRESULT hr = 0;
                if ( freeThreaded )
                {
                    hr = CoCreateInstance( __uuidof( FreeThreadedDOMDocument60 ), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &pInterface ) );
                }
                else
                {
                    hr = CoCreateInstance( __uuidof( DOMDocument60 ), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &pInterface ) );
                }
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Document( pInterface );
            }

            DocumentType Doctype( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMDocumentType *result = nullptr;
                auto hr = pInterface->get_doctype(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return DocumentType(result);
            }
        
            Implementation Implementation( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMImplementation *result = nullptr;
                auto hr = pInterface->get_implementation(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Core::Xml::Dom::Implementation(result);
            }
        
            Element DocumentElement( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMElement *result = nullptr;
                auto hr = pInterface->get_documentElement(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Element(result);
            }
        
            void SetDocumentElement( IXMLDOMElement *DOMElement ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->putref_documentElement(DOMElement);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            Element CreateElement( BSTR tagName ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMElement *result = nullptr;
                auto hr = pInterface->createElement(tagName,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Element(result);
            }

            DocumentFragment CreateDocumentFragment( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMDocumentFragment *result = nullptr;
                auto hr = pInterface->createDocumentFragment(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return DocumentFragment(result);
            }

            Core::Xml::Dom::Text CreateTextNode(BSTR data) const
            {
                auto pInterface = GetInterface();
                IXMLDOMText *result = nullptr;
                auto hr = pInterface->createTextNode(data,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Core::Xml::Dom::Text(result);
            }
            Core::Xml::Dom::Text CreateTextNode( const wchar_t* data ) const
            {
                return CreateTextNode( (BSTR)data );
            }
            template<WideStringLike StringT>
            Core::Xml::Dom::Text CreateTextNode( const StringT& data ) const
            {
                return CreateTextNode( data.c_str( ) );
            }
        
            Comment CreateComment( BSTR data ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMComment *result = nullptr;
                auto hr = pInterface->createComment(data,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Comment(result);
            }
        
            CDATASection CreateCDATASection( BSTR data ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMCDATASection *result = nullptr;
                auto hr = pInterface->createCDATASection(data,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return CDATASection(result);
            }

            ProcessingInstruction CreateProcessingInstruction( BSTR target,BSTR data ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMProcessingInstruction *result = nullptr;
                auto hr = pInterface->createProcessingInstruction(target,data,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return ProcessingInstruction(result);
            }

            Attribute CreateAttribute( BSTR name) const
            {
                auto pInterface = GetInterface();
                IXMLDOMAttribute *result = nullptr;
                auto hr = pInterface->createAttribute(name,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Attribute(result);
            }
        
            EntityReference CreateEntityReference( BSTR name ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMEntityReference *result = nullptr;
                auto hr = pInterface->createEntityReference(name,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return EntityReference(result);
            }
        
            template<typename ElementT = Element>
            NodeList<ElementT> ElementsByTagName( BSTR tagName ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNodeList *result = nullptr;
                auto hr = pInterface->getElementsByTagName(tagName,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return NodeList<ElementT>(result);
            }

            /// <summary>
            /// Creates a node using the supplied type, name, and namespace.
            /// </summary>
            /// <typeparam name="NodeT">
            /// The interface wrapper type corresponding to the type argument.
            /// </typeparam>
            /// <param name="Type">
            /// A value that uniquely identifies the node type. This can be specified 
            /// using either the integer value or the string value.
            /// </param>
            /// <param name="name">
            /// 
            /// </param>
            /// <param name="namespaceURI">
            /// The namespace URI. If specified, the node is created in the context of the 
            /// namespaceURI parameter with the prefix specified on the node name. If the name 
            /// parameter does not have a prefix, this is treated as the default namespace.
            /// </param>
            /// <returns>
            /// A wrapper object for the new node.
            /// </returns>
            /// <remarks>
            /// <para>
            /// The name parameter depends on the value of the Type parameter:
            /// </para>
            /// <list type="table">
            ///     <item>
            ///         <term>NodeType::Attribute</term>
            ///         <description>The name of the attribute.</description>
            ///     </item>
            ///      <item>
            ///         <term>NodeType::CDataSection, NodeType::Comment, NodeType::Document, NodeType::DocumentFragment and NodeType::Text</term>
            ///         <description>The nodeName property for these node types is a constant value; the name parameter is ignored.</description>
            ///     </item>
            ///     <item>
            ///         <term>NodeType::Element</term>
            ///         <description>The name of the XML tag, with any namespace prefix included if present.</description>
            ///     </item>
            ///      <item>
            ///         <term>NodeType::Entity</term>
            ///         <description>The name of the entity.</description>
            ///     </item>
            ///       <item>
            ///         <term>NodeType::EntityReference</term>
            ///         <description>
            ///             The name of the entity referenced. The name does not include the leading ampersand or the trailing semicolon. The name includes the namespace, if one is present.
            ///         </description>
            ///     </item>
            ///     <item>
            ///         <term>NodeType::Notation</term>
            ///         <description>
            ///             The name of the notation.
            ///         </description>
            ///     </item>
            ///     <item>
            ///         <term>NodeType::ProcessingInstruction</term>
            ///         <description>
            ///             The target, the first token following the &lt;? characters.
            ///         </description>
            ///     </item>
            /// </list>
            /// <para>
            /// You cannot create a node of type NodeType::Document, NodeType::DocumentType, NodeType::Entity, or NodeType::Notation.
            /// </para>
            /// <para>
            /// When a node is created, it is created in the context of a namespace if one is supplied (if the namespaceURI parameter 
            /// is supplied). If one is not supplied, the node is created in the namespace of the document. If the namespaceURI 
            /// parameter is specified, the node is created in the context of the namespaceURI parameter with the prefix specified on 
            /// the node name.
            /// </para>
            /// <para>
            /// For node types that do not have names, the empty string, L"", should be passed as the name parameter.
            /// </para>
            /// <para>
            /// For elements and entity references, when the value of the namespaceURI parameter is anything other 
            /// than L"", and the value of the name parameter does not contain a prefix (xxx in xxx:yyy), the value 
            /// of the namespaceURI parameter is treated as the default namespace.
            /// </para>
            /// <para>
            /// Attributes cannot be scoped to a default namespace, and other elements are not qualified to a particular 
            /// namespace; they are treated as being from the namespace defined by the document itself.
            /// </para>
            /// <para>
            /// When the value of namespaceURI parameter is the empty string, L"", the node is created without a namespace. 
            /// Creating a qualified node without specifying a nonempty namespaceURI returns an error. This member is an 
            /// extension of the Worldwide Web Consortium (W3C) Document Object Model (DOM).
            /// </para>
            /// </remarks>
            template<typename NodeT = Node>
            NodeT CreateNode( const VARIANT& type,BSTR name,BSTR namespaceURI) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->createNode(type,name,namespaceURI,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }

            template<typename NodeT = Node>
            NodeT CreateNode( const Dom::NodeType type, BSTR name, BSTR namespaceURI ) const
            {
                Variant typeVar( static_cast< Int32 >( type ) );
                NodeT CreateNode( typeVar, name, namespaceURI );
            }


            template<typename NodeT = Node>
            NodeT NodeFromID( BSTR idString ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->nodeFromID(idString,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                if constexpr ( std::is_same_v<std::remove_cvref_t<NodeT>, Node> )
                {
                    return NodeT( result );
                }
                else
                {
                    using InterfaceType = typename NodeT::InterfaceType;
                    InterfaceType* pNodeType = nullptr;
                    hr = result->QueryInterface<InterfaceType>( &pNodeType );
                    HCC_COM_CHECK_HRESULT2( hr, result );
                    NodeT node( pNodeType );
                    result->Release( );
                    return node;
                }
            }
        
            bool Load(const VARIANT& xmlSource) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->load(xmlSource,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }
            bool Load( const wchar_t* xmlSource ) const
            {
                Variant variant( xmlSource );
                return Load( variant );
            }

            bool Load( const WideString& xmlSource ) const
            {
                Variant variant( xmlSource );
                return Load( variant );
            }


        
            long ReadyState( ) const
            {
                auto pInterface = GetInterface();
                long result = VARIANT_FALSE;
                auto hr = pInterface->get_readyState(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
        
            ParseError ParseError( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMParseError* result = nullptr;
                auto hr = pInterface->get_parseError(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Core::Xml::Dom::ParseError(result);
            }

            XmlString Url( ) const
            {
                auto pInterface = GetInterface();
                BSTR result = nullptr;
                auto hr = pInterface->get_url(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return XmlString(result,true);
            }
        
            bool Async( ) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->get_async(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }

            void SetAsync( bool isAsync = true) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_async(isAsync?VARIANT_TRUE:VARIANT_FALSE);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            void Abort( void) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->abort( );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            bool LoadXML( BSTR bstrXML ) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->loadXML(bstrXML,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }

            bool LoadXML( const wchar_t* xml ) const
            {
                return LoadXML( (BSTR)xml );
            }
            bool LoadXML( const WideString& xml ) const
            {
                return LoadXML( (BSTR)xml.c_str() );
            }


            void Save( const VARIANT& destination ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->save( destination );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }

            void Save(const WideString& destination) const
            {
                Variant arg( destination );
                Save(arg);
            }

            void Save( IStream* destination ) const
            {
                Variant arg( destination ); 
                Save(arg);
            }


        
            bool ValidateOnParse( ) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->get_validateOnParse(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }
        
            void SetValidateOnParse( bool isValidating = true) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_validateOnParse(isValidating?VARIANT_TRUE:VARIANT_FALSE);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }

            bool ResolveExternals( ) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->get_resolveExternals(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }

            void SetResolveExternals( bool isResolving = true) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_resolveExternals(isResolving?VARIANT_TRUE:VARIANT_FALSE);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            bool PreserveWhiteSpace( ) const
            {
                auto pInterface = GetInterface();
                VARIANT_BOOL result = VARIANT_FALSE;
                auto hr = pInterface->get_preserveWhiteSpace(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result != VARIANT_FALSE;
            }
        

            void SetPreserveWhiteSpace( bool isPreserving = true) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->put_preserveWhiteSpace(isPreserving?VARIANT_TRUE:VARIANT_FALSE);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            /*
            HRESULT STDMETHODCALLTYPE put_onreadystatechange( VARIANT readystatechangeSink);
        
            HRESULT STDMETHODCALLTYPE put_ondataavailable( VARIANT ondataavailableSink);
        
            HRESULT STDMETHODCALLTYPE put_ontransformnode( VARIANT ontransformnodeSink);
            */

            SchemaCollection Namespaces( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMSchemaCollection *result = nullptr;
                auto hr = pInterface->get_namespaces(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return SchemaCollection(result);
            }
        
            /*
            HRESULT STDMETHODCALLTYPE get_schemas(VARIANT *otherCollection);
        
            HRESULT STDMETHODCALLTYPE putref_schemas( VARIANT otherCollection);
            */

            Core::Xml::Dom::ParseError Validate() const
            {
                auto pInterface = GetInterface();
                IXMLDOMParseError* result = nullptr;
                auto hr = pInterface->validate(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Core::Xml::Dom::ParseError(result);
            }
        
            void SetProperty( BSTR name, const VARIANT& value) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->setProperty(name,value);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }
        
            Variant GetProperty( BSTR name) const
            {
                auto pInterface = GetInterface();
                Variant result;
                auto hr = pInterface->getProperty(name,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return result;
            }
                        
            Core::Xml::Dom::ParseError validateNode(IXMLDOMNode *node) const
            {
                auto pInterface = GetInterface();
                IXMLDOMParseError* result = nullptr;
                auto hr = pInterface->validateNode(node,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Core::Xml::Dom::ParseError(result);
            }
        
            Node ImportNode( IXMLDOMNode *node,bool deep = true) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode* result;
                auto hr = pInterface->importNode(node,deep?VARIANT_TRUE:VARIANT_FALSE,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }

        };



        inline Document Node::OwnerDocument( ) const
        {
            auto pInterface = GetInterface();
            IXMLDOMDocument *pDocument = nullptr;
            auto hr = pInterface->get_ownerDocument(&pDocument);
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            IXMLDOMDocument3* pDocument3 = nullptr;

            hr = pDocument->QueryInterface<IXMLDOMDocument3>(&pDocument3);
            pDocument->Release();
            HCC_COM_CHECK_HRESULT2( hr, pInterface );

            return Document(pDocument3);
        }
    }

    class XTLRuntime : public Dom::Node
    {
    public:
        using XmlString = Dom::XmlString;
        typedef Dom::Node Base;
        HCC_COM_STANDARD_METHODS_IMPL( XTLRuntime, Node, IXTLRuntime, IXMLDOMNode )


            Int32 UniqueID( IXMLDOMNode* node ) const
        {
            auto pInterface = GetInterface( );
            long result = 0;
            auto hr = pInterface->uniqueID( node, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        Int32 Depth( IXMLDOMNode* node ) const
        {
            auto pInterface = GetInterface( );
            long result = 0;
            auto hr = pInterface->depth( node, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        Int32 ChildNumber( IXMLDOMNode* node ) const
        {
            auto pInterface = GetInterface( );
            long result = 0;
            auto hr = pInterface->childNumber( node, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        Int32 AncestorChildNumber( BSTR nodeName, IXMLDOMNode* node ) const
        {
            auto pInterface = GetInterface( );
            long result = 0;
            auto hr = pInterface->ancestorChildNumber( nodeName, node, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        Int32 AbsoluteChildNumber( IXMLDOMNode* node ) const
        {
            auto pInterface = GetInterface( );
            long result = 0;
            auto hr = pInterface->absoluteChildNumber( node, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return result;
        }

        XmlString FormatIndex( Int32 index, BSTR format ) const
        {
            auto pInterface = GetInterface( );
            BSTR result = nullptr;
            auto hr = pInterface->formatIndex( index, format, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return XmlString( result, true );
        }

        XmlString FormatNumber( double number, BSTR format ) const
        {
            auto pInterface = GetInterface( );
            BSTR result = nullptr;
            auto hr = pInterface->formatNumber( number, format, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return XmlString( result, true );
        }

        XmlString FormatDate( const VARIANT& date, BSTR format, const VARIANT& destLocale ) const
        {
            auto pInterface = GetInterface( );
            BSTR result = nullptr;
            auto hr = pInterface->formatDate( date, format, destLocale, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return XmlString( result, true );
        }

        XmlString FormatTime( const VARIANT& date, BSTR format, const VARIANT& destLocale ) const
        {
            auto pInterface = GetInterface( );
            BSTR result = nullptr;
            auto hr = pInterface->formatTime( date, format, destLocale, &result );
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return XmlString( result, true );
        }
    };


    namespace Sax
    {
    }
};


#endif 