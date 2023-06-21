#pragma once
#ifndef __HCCXML_H__
#define __HCCXML_H__

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

        class NodeList;
        class NamedNodeMap;
        class Document;

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
        
            Node ParentNode( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_parentNode(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            NodeList ChildNodes( ) const;
        
            Node FirstChild( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_firstChild(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            Node LastChild( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_lastChild(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            Node PreviousSibling( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_previousSibling(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            Node NextSibling( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_nextSibling(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            NamedNodeMap Attributes() const;
        
            Node InsertBefore( IXMLDOMNode *newChild,const VARIANT& refChild) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->insertBefore( newChild, refChild,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            Node ReplaceChild( IXMLDOMNode *newChild,IXMLDOMNode *oldChild) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->replaceChild( newChild, oldChild,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            Node RemoveChild( IXMLDOMNode *childNode ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->removeChild( childNode,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            Node AppendChild( IXMLDOMNode *newChild ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->appendChild( newChild,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
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
        
            Node CloneNode( bool deep = true) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->cloneNode( deep?VARIANT_TRUE:VARIANT_FALSE,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
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

            void SetText( const XmlString& text ) const
            {
                auto pInterface = GetInterface( );
                auto hr = pInterface->put_text( text.c_str() );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
            }

            void SetText( const wchar_t* text ) const
            {
                XmlString xmlString( text );
                SetText( xmlString );
            }
            void SetText( const WideString& text ) const
            {
                XmlString xmlString( text );
                SetText( xmlString );
            }
            void SetText( const std::string& text ) const
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
        
            Node Definition( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_definition( &result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
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
        
            NodeList SelectNodes( BSTR queryString ) const;

            Node SelectSingleNode( BSTR queryString ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->selectSingleNode( queryString,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
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
            using iterator_category = std::random_access_iterator_tag;
            using value_type = NodeT;
            using difference_type = SSIZE_T;
            using pointer = const value_type*;
            using reference = const value_type&;
        private:
            CollectionType* collection_;
            size_t index_;
            size_t size_;
            Node node_;
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
                        node_ = collection_->Item( static_cast<long>( 0 ) );
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


        class NodeList : public Dispatch
        {
        public:
            using const_iterator = NodeIterator<const NodeList, const Node>;
            using iterator = NodeIterator<NodeList, Node>;
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


            Node Item( long index ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_item(index,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
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

            Node operator[]( size_t index ) const
            {
                return Item( static_cast<long>( index ) );
            }


        
            Node NextNode( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->nextNode(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
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

        inline NodeList Node::ChildNodes( ) const
        {
            auto pInterface = GetInterface();
            IXMLDOMNodeList *result = nullptr;
            auto hr = pInterface->get_childNodes(&result);
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return NodeList(result);
        }


        inline NodeList Node::SelectNodes( BSTR queryString ) const
        {
            auto pInterface = GetInterface();
            IXMLDOMNodeList *result;
            auto hr = pInterface->selectNodes(queryString, &result);
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return NodeList(result);
        }


        class NamedNodeMap : public Dispatch
        {
        public:
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

            Node NamedItem( BSTR name ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->getNamedItem(name,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            Node SetNamedItem( IXMLDOMNode *newItem) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->setNamedItem(newItem,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            Node RemoveNamedItem( BSTR name ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->removeNamedItem(name,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }
        
            Node Item( long index ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result;
                auto hr = pInterface->get_item(index,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
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

            Node operator[]( size_t index ) const
            {
                return Item( static_cast<long>( index ) );
            }

        
            Node QualifiedItem( BSTR baseName,BSTR namespaceURI) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->getQualifiedItem(baseName,namespaceURI,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }

            Node RemoveQualifiedItem( BSTR baseName,BSTR namespaceURI) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->removeQualifiedItem(baseName,namespaceURI,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }

            Node NextNode( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->nextNode(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
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

        inline NamedNodeMap Node::Attributes() const
        {
            auto pInterface = GetInterface();
            IXMLDOMNamedNodeMap *result = nullptr;
            auto hr = pInterface->get_attributes(&result);
            HCC_COM_CHECK_HRESULT2( hr, pInterface );
            return NamedNodeMap(result);
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
        
            NamedNodeMap Entities( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNamedNodeMap *result = nullptr;
                auto hr = pInterface->get_entities(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return NamedNodeMap(result);
            }
        
            NamedNodeMap get_notations( ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNamedNodeMap *result = nullptr;
                auto hr = pInterface->get_notations(&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return NamedNodeMap(result);
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

            NodeList ElementsByTagName( BSTR tagName ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNodeList *result = nullptr;
                auto hr = pInterface->getElementsByTagName(tagName,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return NodeList(result);
            }

            NodeList ElementsByTagName( const wchar_t* tagName ) const
            {
                return ElementsByTagName( (BSTR)tagName );
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

        
            void Normalize( ) const
            {
                auto pInterface = GetInterface();
                auto hr = pInterface->normalize( );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
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


            explicit Document( const wchar_t* xml, bool validateOnParse = false, bool resolveExternals = false, bool preserveWhiteSpace = false, bool async = false )
            {
                IXMLDOMDocument3* pInterface = nullptr;
                HRESULT hr = CoCreateInstance( __uuidof( DOMDocument60 ), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &pInterface ) );
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                ResetPtr( pInterface );
                SetValidateOnParse( validateOnParse );
                SetResolveExternals( resolveExternals );
                SetPreserveWhiteSpace( preserveWhiteSpace );
                SetAsync( async );
                LoadXML( xml );
            }

            explicit Document( const WideString& xml, bool validateOnParse = false, bool resolveExternals = false, bool preserveWhiteSpace = false, bool async = false )
                : Document( xml.c_str(), validateOnParse, resolveExternals, preserveWhiteSpace, async )
            {
            }



            static Document Create( )
            {
                IXMLDOMDocument3* pInterface = nullptr;
                HRESULT hr = CoCreateInstance( __uuidof( DOMDocument60 ), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS( &pInterface ) );
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
        
            NodeList ElementsByTagName( BSTR tagName ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNodeList *result = nullptr;
                auto hr = pInterface->getElementsByTagName(tagName,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return NodeList(result);
            }

            Node CreateNode( const VARIANT& Type,BSTR name,BSTR namespaceURI,IXMLDOMNode **node) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->createNode(Type,name,namespaceURI,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
            }

            Node NodeFromID( BSTR idString ) const
            {
                auto pInterface = GetInterface();
                IXMLDOMNode *result = nullptr;
                auto hr = pInterface->nodeFromID(idString,&result);
                HCC_COM_CHECK_HRESULT2( hr, pInterface );
                return Node(result);
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

    namespace Sax
    {
    }
};


#endif 