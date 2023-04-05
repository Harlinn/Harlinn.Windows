#pragma once
#ifndef HARLINN_COMMON_CONFIG_HCCFG_NODE_H_
#define HARLINN_COMMON_CONFIG_HCCFG_NODE_H_

#include "hccfg_export.h"
#include <HCCGuid.h>
#include <HCCDateTime.h>
#include <HCCCurrency.h>
#include <HCCString.h>
#include <HCCLib.h>
#include <xxhash_cx.h>
#include <HCCReference.h>
#include <HCCSync.h>

namespace Harlinn::Common::Config
{ 
	namespace hcc = Harlinn::Common::Core;
	using namespace xxhash::literals;

	

	enum class NodeType : hcc::Byte
	{
		HCC_MAP_BASICTYPEID_ENUM_VALUES( hcc::Byte ),
		String,
		WideString,
		Element,
		Sequence,
		Elements,
		GroupRef,
		EnvironmentValue,
		Environment,
		Root
	};

#define HCCFG_NOTIFICATIONID(_notificationName_) \
	static constexpr uint64_t _notificationName_##NotificationId = #_notificationName_##_xxh64

	class ValueBase;
	class Container;
	class Element;
	class Sequence;
	class Elements;
	class EnvironmentValue;
	class Environment;
	class Root;


	class XmlParserOptions
	{
	public:
		enum class ValidationScheme
		{
			Never = 0,
			Always,
			Auto
		};
		// Indicates whether namespace processing should be done.
		bool enableNamespaces_ = false;
		// Indicates whether schema processing should be done.
		bool enableSchema_ = false;
		// Indicates whether full schema constraint checking should be done.
		bool enableFullSchemaChecking_ = false;

		bool createEntityReferenceNodes_ = false;
		bool useFilter_ = false;
		ValidationScheme validationScheme_ = ValidationScheme::Auto;
	public:
		constexpr XmlParserOptions( ) = default;

		constexpr bool EnableNamespaces( ) const noexcept
		{
			return enableNamespaces_;
		}

		constexpr bool EnableSchema( ) const noexcept
		{
			return enableSchema_;
		}

		constexpr bool EnableFullSchemaChecking( ) const noexcept
		{
			return enableFullSchemaChecking_;
		}

		constexpr bool CreateEntityReferenceNodes( ) const noexcept
		{
			return createEntityReferenceNodes_;
		}

		constexpr bool UseFilter( ) const noexcept
		{
			return useFilter_;
		}

		constexpr ValidationScheme ValidationScheme( ) const noexcept
		{
			return validationScheme_;
		}


	};

	HCCFG_EXPORT void LoadFromURI( Element& element, const std::wstring& filename, const XmlParserOptions& options = XmlParserOptions() );
	
	class Node : public hcc::ReferenceCounted
	{
		friend class ValueBase;
		friend class Container;
		friend class Element;
		friend class Sequence;
		friend class Elements;
		friend class Environment;
		friend class Config::Root;
	public:
		using Base = hcc::ReferenceCounted;
		using NameType = std::wstring;
		using NameViewType = std::wstring_view;
		HCCFG_NOTIFICATIONID( Deleted );
		boost::signals2::signal<void( Node* sender, uint64_t notificationId, void* data )> OnNotification;
	private:
		// immutable, changing the owner of a node is not a valid operation
		Node* const owner_ = nullptr;
		// immutable, changing the type of a node is not a valid operation
		const NodeType type_ = NodeType::Unknown;
		// immutable, changing the name of a node is not a valid operation
		const NameType name_;

		Node( Node* owner, NodeType type, const NameType& name ) noexcept
			: owner_( owner ), type_( type ), name_( name )
		{ }
		Node( Node* owner, NodeType type, NameType&& name ) noexcept
			: owner_( owner ), type_( type ), name_( std::move(name) )
		{ }
		Node( Node* owner, NodeType type, const NameViewType& name ) noexcept
			: owner_( owner ), type_( type ), name_( name )
		{ }
	protected:
		void DoOnNotification( uint64_t notificationId = 0, void* data = nullptr ) const
		{
			OnNotification( const_cast<Node*>( this ), notificationId, data );
			NotifyOwner( const_cast<Node*>( this ), notificationId, data );
		}
	private:
		void NotifyOwner( Node* sender, uint64_t notificationId, void* data ) const
		{
			if ( owner_ )
			{
				owner_->DoOnChildNotification( sender, notificationId, data );
			}
		}
		void DoOnChildNotification( Node* sender, uint64_t notificationId, void* data ) const
		{
			OnNotification( sender, notificationId, data );
			NotifyOwner( sender, notificationId, data );
		}
	protected:
		virtual void DoOnDelete( )
		{
			this->DoOnNotification( DeletedNotificationId, this );
		}
	public:
		HCCFG_EXPORT virtual ~Node( );

		std::wstring Path( ) const
		{
			if ( owner_ )
			{
				return owner_->Path( ) + L"/" + name_;
			}
			else
			{
				return name_;
			}
		}

		Node* Owner( ) const noexcept
		{
			return owner_;
		}
		NodeType Type( ) const noexcept
		{
			return type_;
		}
		const NameType& Name( ) const noexcept
		{
			return name_;
		}
	private:
		bool InternalIsChildOf( Node* ownerNode ) const noexcept
		{
			if ( owner_ )
			{
				if ( owner_ != ownerNode )
				{
					return owner_->InternalIsChildOf( ownerNode );
				}
				return true;
			}
			return false;
		}
	public:
		bool IsChildOf( Node* ownerNode ) const noexcept
		{
			if ( ownerNode )
			{
				return InternalIsChildOf( ownerNode );
			}
			return false;
		}

		inline virtual hcc::Reference<Config::Root> Root( ) const;

		HCCFG_EXPORT virtual hcc::Reference<Node> Find( const std::wstring_view& name ) const;
		HCCFG_EXPORT virtual hcc::Reference<Node> FindByPath( const std::wstring_view& path ) const;

	};

	namespace Internal
	{
		hcc::Reference<Node> FindByPath( const hcc::Reference<Node>& node, const std::wstring_view& path );
	}
	template<typename T, NodeType nodeType>
	class ValueT;

	class ValueBase : public Node
	{
		friend class EnvironmentValue;
		template<typename T, NodeType nodeType>
		friend class ValueT;
	public:
		using Base = Node;
		HCCFG_NOTIFICATIONID( ValueChanged );
	private:
		ValueBase( Node* owner, NodeType type, const NameType& name ) noexcept
			: Base( owner, type, name )
		{
		}
		ValueBase( Node* owner, NodeType type, NameType&& name ) noexcept
			: Base( owner, type, std::move( name ) )
		{
		}
		ValueBase( Node* owner, NodeType type, const NameViewType& name ) noexcept
			: Base( owner, type, name )
		{
		}
	};

	class Container : public Node
	{
		template<typename T, NodeType nodeType>
		friend class ValueT;
		friend class Environment;
		friend class Sequence;
		friend class Element;
		friend class Elements;
		friend class Config::Root;
	public:
		using Base = Node;
		HCCFG_NOTIFICATIONID( Inserted );
		HCCFG_NOTIFICATIONID( Cleared );
	private:
		using MutexType = hcc::SlimReaderWriterLock;
		using WriterLock = std::unique_lock<MutexType>;
		using ReaderLock = std::shared_lock<MutexType>;

		mutable MutexType mutex_;

		Container( Node* owner, NodeType type, const NameType& name ) noexcept
			: Base( owner, type, name )
		{
		}
		Container( Node* owner, NodeType type, NameType&& name ) noexcept
			: Base( owner, type, std::move( name ) )
		{
		}
		Container( Node* owner, NodeType type, const NameViewType& name ) noexcept
			: Base( owner, type, name )
		{
		}
	};


	class GroupRef : public ValueBase
	{
	public:
		using Base = ValueBase;
	private:
	};

	template<typename T, NodeType nodeType>
	class ValueT : public ValueBase
	{
		friend class Element;
		friend class Sequence;
	public:
		using Base = ValueBase;
		using ValueType = T;
		static constexpr NodeType NODETYPE = nodeType;
	private:
		ValueType value_;

		ValueT( Node* owner, const NameType& name ) noexcept
			: Base( owner, NODETYPE, name )
		{
		}
		ValueT( Node* owner, NameType&& name ) noexcept
			: Base( owner, NODETYPE, std::move( name ) )
		{
		}

		ValueT( Node* owner, const NameViewType& name ) noexcept
			: Base( owner, NODETYPE, name )
		{
		}

		ValueT( Node* owner, const NameType& name, const ValueType& value ) noexcept
			: Base( owner, NODETYPE, name )
		{
		}
		ValueT( Node* owner, NameType&& name, const ValueType& value ) noexcept
			: Base( owner, NODETYPE, std::move( name ) )
		{
		}
		ValueT( Node* owner, const NameViewType& name, const ValueType& value ) noexcept
			: Base( owner, NODETYPE, name )
		{
		}
	public:
		const ValueType& Value( ) const noexcept;
		bool SetValue( const ValueType& value );
	};

	using BooleanValue = ValueT<bool, NodeType::Boolean>;
	using CharValue = ValueT<char, NodeType::Char>;
	using SByteValue = ValueT<hcc::SByte, NodeType::SByte>;
	using ByteValue = ValueT<hcc::Byte, NodeType::Byte>;
	using WCharValue = ValueT<wchar_t, NodeType::WChar>;
	using Int16Value = ValueT<hcc::Int16, NodeType::Int16>;
	using UInt16Value = ValueT<hcc::UInt16, NodeType::UInt16>;
	using Int32Value = ValueT<hcc::Int32, NodeType::Int32>;
	using UInt32Value = ValueT<hcc::UInt32, NodeType::UInt32>;
	using Int64Value = ValueT<hcc::Int64, NodeType::Int64>;
	using UInt64Value = ValueT<hcc::UInt64, NodeType::UInt64>;
	using SingleValue = ValueT<hcc::Single, NodeType::Single>;
	using DoubleValue = ValueT<hcc::Double, NodeType::Double>;
	using TimeSpanValue = ValueT<hcc::TimeSpan, NodeType::TimeSpan>;
	using DateTimeValue = ValueT<hcc::DateTime, NodeType::DateTime>;
	using CurrencyValue = ValueT<hcc::Currency, NodeType::Currency>;
	using GuidValue = ValueT<hcc::Guid, NodeType::Guid>;
	using StringValue = ValueT<std::string, NodeType::String>;
	using WideStringValue = ValueT<std::wstring, NodeType::WideString>;



	class Element : public Container
	{
		template<typename T, NodeType nodeType>
		friend class ValueT;
		friend class Sequence;
		friend class Elements;
		friend hcc::Reference<Node> Internal::FindByPath( const hcc::Reference<Node>& node, const std::wstring_view& path );
	public:
		using Base = Container;
		static constexpr NodeType NODETYPE = NodeType::Element;
	private:
		std::map<std::wstring_view, hcc::Reference<Node> > items_;

		Element( Node* owner, const NameType& name ) noexcept
			: Base( owner, NodeType::Element, name )
		{
		}
		Element( Node* owner, NameType&& name ) noexcept
			: Base( owner, NodeType::Element, std::move( name ) )
		{
		}
		Element( Node* owner, const NameViewType& name ) noexcept
			: Base( owner, NodeType::Element, name )
		{
		}

		template<typename T>
		hcc::Reference<T> Add( const std::wstring_view& name, const typename T::ValueType& value )
		{
			bool nodeExisted = false;
			hcc::Reference<T> result;
			{
				WriterLock lock( mutex_ );
				auto it = items_.find( name );
				if ( it == items_.end( ) )
				{
					result.reset( new T( this, name, value ) );
					std::wstring_view sv = result->Name( );
					items_.emplace( sv, result );
				}
				else
				{
					auto result = it->second;
					if ( result->Type( ) != T::NODETYPE )
					{
						HCC_THROW( hcc::Exception, L"Unexpected node type" );
					}
					nodeExisted = true;
				}
			}
			if ( nodeExisted )
			{
				result->SetValue( value );
			}
			else
			{
				Element::ReaderLock lock( mutex_ );
				this->DoOnNotification( InsertedNotificationId, result.get() );
			}
			return result;
		}

		template<typename T>
		hcc::Reference<T> Add( const std::wstring_view& name )
		{ 
			bool inserted = false;
			hcc::Reference<T> result;
			{
				WriterLock lock( mutex_ );
				auto it = items_.find( name );
				if ( it == items_.end( ) )
				{
					result.reset( new T( this, name ) );
					std::wstring_view sv = result->Name( );
					items_.emplace( sv, result );
					inserted = true;
				}
				else
				{
					auto result = it->second;
					if ( result->Type( ) != T::NODETYPE )
					{
						HCC_THROW( hcc::Exception, L"Unexpected node type" );
					}
				}
			}
			if ( inserted )
			{
				Element::ReaderLock lock( mutex_ );
				this->DoOnNotification( InsertedNotificationId, result.get( ) );
			}
			return result;
		}
	protected:
		virtual void DoOnDelete( )
		{
			for ( const auto& entry : items_ )
			{
				entry.second->DoOnDelete( );
			}
			Base::DoOnDelete( );
		}
	public:
		const std::map<std::wstring_view, hcc::Reference<Node> >& Items( ) const
		{
			return items_;
		}

		bool IsEmpty( ) const
		{
			ReaderLock lock( mutex_ );
			return items_.empty( );
		}

		bool Contains( const std::wstring_view& name )
		{
			ReaderLock lock( mutex_ );
			return items_.contains( name );
		}
		size_t Size( ) const
		{
			ReaderLock lock( mutex_ );
			return items_.size( );
		}


		hcc::Reference<Node> Find( const std::wstring_view& name ) const
		{
			ReaderLock lock( mutex_ );
			auto it = items_.find( name );
			if ( it != items_.end( ) )
			{
				return it->second;
			}
			return hcc::Reference<Node>( );
		}

		hcc::Reference<Node> operator[]( const std::wstring_view& name ) const
		{
			return Find( name );
		}

		template<typename T>
		hcc::Reference<T> Find( const std::wstring_view& name ) const
		{
			return hcc::Reference<T>( static_cast<T*>(Find( name ).release() ) );
		}

		bool Delete( const std::wstring_view& name )
		{
			hcc::Reference<Node> foundNode;
			{
				WriterLock lock( mutex_ );
				auto it = items_.find( name );
				if ( it != items_.end( ) )
				{
					foundNode = it->second;
					items_.erase( it );
				}
			}
			if ( foundNode )
			{
				foundNode->DoOnDelete( );
			}
		}
		bool Clear( )
		{
			std::map<std::wstring_view, hcc::Reference<Node> > items;
			{
				WriterLock lock( mutex_ );
				items = std::move( items_ );
			}
			for ( auto& ref : items )
			{
				ref.second->DoOnDelete( );
			}
			{
				ReaderLock lock( mutex_ );
				this->DoOnNotification( ClearedNotificationId, this );
			}
		}

		void LoadFromURI( const std::wstring& name )
		{
			Config::LoadFromURI( *this, name );
		}

		HCCFG_EXPORT hcc::Reference<Element> AddElement( const std::wstring_view& name );
		HCCFG_EXPORT hcc::Reference<Sequence> AddSequence( const std::wstring_view& name );
		HCCFG_EXPORT hcc::Reference<BooleanValue> AddBoolean( const std::wstring_view& name, bool value = {} );
		HCCFG_EXPORT hcc::Reference<CharValue> AddChar( const std::wstring_view& name, char value = {} );
		HCCFG_EXPORT hcc::Reference<SByteValue> AddSByte( const std::wstring_view& name, hcc::SByte value = {} );
		HCCFG_EXPORT hcc::Reference<ByteValue> AddByte( const std::wstring_view& name, hcc::Byte value = {} );
		HCCFG_EXPORT hcc::Reference<WCharValue> AddWChar( const std::wstring_view& name, wchar_t value = {} );
		HCCFG_EXPORT hcc::Reference<Int16Value> AddInt16( const std::wstring_view& name, hcc::Int16 value = {} );
		HCCFG_EXPORT hcc::Reference<UInt16Value> AddUInt16( const std::wstring_view& name, hcc::UInt16 value = {} );
		HCCFG_EXPORT hcc::Reference<Int32Value> AddInt32( const std::wstring_view& name, hcc::Int32 value = {} );
		HCCFG_EXPORT hcc::Reference<UInt32Value> AddUInt32( const std::wstring_view& name, hcc::UInt32 value = {} );
		HCCFG_EXPORT hcc::Reference<Int64Value> AddInt64( const std::wstring_view& name, hcc::Int64 value = {} );
		HCCFG_EXPORT hcc::Reference<UInt64Value> AddUInt64( const std::wstring_view& name, hcc::UInt64 value = {} );
		HCCFG_EXPORT hcc::Reference<SingleValue> AddSingle( const std::wstring_view& name, hcc::Single value = {} );
		HCCFG_EXPORT hcc::Reference<DoubleValue> AddDouble( const std::wstring_view& name, hcc::Double value = {} );
		HCCFG_EXPORT hcc::Reference<TimeSpanValue> AddTimeSpan( const std::wstring_view& name, hcc::TimeSpan value = {} );
		HCCFG_EXPORT hcc::Reference<DateTimeValue> AddDateTime( const std::wstring_view& name, hcc::DateTime value = {} );
		HCCFG_EXPORT hcc::Reference<CurrencyValue> AddCurrency( const std::wstring_view& name, hcc::Currency value = {} );
		HCCFG_EXPORT hcc::Reference<GuidValue> AddGuid( const std::wstring_view& name, hcc::Guid value = {} );
		HCCFG_EXPORT hcc::Reference<StringValue> AddString( const std::wstring_view& name, const std::string& value = {} );
		HCCFG_EXPORT hcc::Reference<WideStringValue> AddWideString( const std::wstring_view& name, const std::wstring& value = {} );
		HCCFG_EXPORT hcc::Reference<Node> FindByPath( const std::wstring_view& path ) const;


	};

	template<typename T, NodeType nodeType>
	const T& ValueT<T, nodeType>::Value( ) const noexcept
	{
		Container* container = static_cast<Container*>( Owner() );
		Container::ReaderLock lock( container->mutex_ );
		return value_;
	}
	template<typename T, NodeType nodeType>
	bool ValueT<T, nodeType>::SetValue( const T& value )
	{
		Container* container = static_cast<Container*>( Owner( ) );
		bool result = false;
		{
			Container::WriterLock lock( container->mutex_ );
			if ( value_ != value )
			{
				value_ = value;
				result = true;
			}
		}
		if ( result )
		{
			Container::ReaderLock lock( container->mutex_ );
			this->DoOnNotification( ValueChangedNotificationId, &value_ );
		}
		return result;
	}

	class Sequence : public Container
	{
		template<typename T, NodeType nodeType>
		friend class ValueT;
		friend class Element;
		friend hcc::Reference<Node> Internal::FindByPath( const hcc::Reference<Node>& node, const std::wstring_view& path );
	public:
		using Base = Container;
		static constexpr NodeType NODETYPE = NodeType::Sequence;
	private:
		std::vector< hcc::Reference<Node> > items_;

		Sequence( Node* owner, const NameType& name ) noexcept
			: Base( owner, NodeType::Sequence, name )
		{
		}
		Sequence( Node* owner, NameType&& name ) noexcept
			: Base( owner, NodeType::Sequence, std::move( name ) )
		{
		}
		Sequence( Node* owner, const NameViewType& name ) noexcept
			: Base( owner, NodeType::Sequence, name )
		{
		}

		template<typename T, typename ...Args >
		hcc::Reference<T> Add( const std::wstring_view& name, Args&& ...args )
		{
			hcc::Reference<T> result;
			{
				WriterLock lock( mutex_ );
				result.reset( new T( this, name, std::forward<Args>(args)... ) );
				items_.emplace_back( result );
			}
			{
				Element::ReaderLock lock( mutex_ );
				this->DoOnNotification( InsertedNotificationId, result.get( ) );
			}
			return result;
		}
	protected:
		virtual void DoOnDelete( )
		{
			for ( const auto& entry : items_ )
			{
				entry->DoOnDelete( );
			}
			Base::DoOnDelete( );
		}
	public:
		const std::vector< hcc::Reference<Node> >& Items( ) const
		{
			return items_;
		}

		const hcc::Reference<Node>& at( size_t index ) const
		{
			return items_.at( index );
		}
		const hcc::Reference<Node>& operator[]( size_t index ) const
		{
			return items_[ index ];
		}

		bool IsEmpty( ) const
		{
			ReaderLock lock( mutex_ );
			return items_.empty( );
		}

		size_t Size( ) const
		{
			ReaderLock lock( mutex_ );
			return items_.size( );
		}

		bool Delete( size_t offset )
		{
			hcc::Reference<Node> ref;
			{
				WriterLock lock( mutex_ );
				if ( offset < items_.size( ) )
				{
					ref = items_[offset];
					items_.erase( items_.begin( ) + offset );
				}
			}
			if ( ref )
			{
				ref->DoOnDelete( );
			}
		}

		bool Clear( )
		{
			std::vector< hcc::Reference<Node> > refs;
			{
				WriterLock lock( mutex_ );
				refs = std::move( items_ );
			}
			for ( auto& ref : refs )
			{
				ref->DoOnDelete( );
			}
			{
				ReaderLock lock( mutex_ );
				this->DoOnNotification( ClearedNotificationId, this );
			}
		}

		HCCFG_EXPORT virtual hcc::Reference<Node> Find( const std::wstring_view& name ) const;

		HCCFG_EXPORT hcc::Reference<Element> AddElement( const std::wstring_view& name );
		HCCFG_EXPORT hcc::Reference<Sequence> AddSequence( const std::wstring_view& name );
		HCCFG_EXPORT hcc::Reference<BooleanValue> AddBoolean( const std::wstring_view& name, bool value = {} );
		HCCFG_EXPORT hcc::Reference<CharValue> AddChar( const std::wstring_view& name, char value = {} );
		HCCFG_EXPORT hcc::Reference<SByteValue> AddSByte( const std::wstring_view& name, hcc::SByte value = {} );
		HCCFG_EXPORT hcc::Reference<ByteValue> AddByte( const std::wstring_view& name, hcc::Byte value = {} );
		HCCFG_EXPORT hcc::Reference<WCharValue> AddWChar( const std::wstring_view& name, wchar_t value = {} );
		HCCFG_EXPORT hcc::Reference<Int16Value> AddInt16( const std::wstring_view& name, hcc::Int16 value = {} );
		HCCFG_EXPORT hcc::Reference<UInt16Value> AddUInt16( const std::wstring_view& name, hcc::UInt16 value = {} );
		HCCFG_EXPORT hcc::Reference<Int32Value> AddInt32( const std::wstring_view& name, hcc::Int32 value = {} );
		HCCFG_EXPORT hcc::Reference<UInt32Value> AddUInt32( const std::wstring_view& name, hcc::UInt32 value = {} );
		HCCFG_EXPORT hcc::Reference<Int64Value> AddInt64( const std::wstring_view& name, hcc::Int64 value = {} );
		HCCFG_EXPORT hcc::Reference<UInt64Value> AddUInt64( const std::wstring_view& name, hcc::UInt64 value = {} );
		HCCFG_EXPORT hcc::Reference<SingleValue> AddSingle( const std::wstring_view& name, hcc::Single value = {} );
		HCCFG_EXPORT hcc::Reference<DoubleValue> AddDouble( const std::wstring_view& name, hcc::Double value = {} );
		HCCFG_EXPORT hcc::Reference<TimeSpanValue> AddTimeSpan( const std::wstring_view& name, hcc::TimeSpan value = {} );
		HCCFG_EXPORT hcc::Reference<DateTimeValue> AddDateTime( const std::wstring_view& name, hcc::DateTime value = {} );
		HCCFG_EXPORT hcc::Reference<CurrencyValue> AddCurrency( const std::wstring_view& name, hcc::Currency value = {} );
		HCCFG_EXPORT hcc::Reference<GuidValue> AddGuid( const std::wstring_view& name, hcc::Guid value = {} );
		HCCFG_EXPORT hcc::Reference<StringValue> AddString( const std::wstring_view& name, const std::string& value = {} );
		HCCFG_EXPORT hcc::Reference<WideStringValue> AddWideString( const std::wstring_view& name, const std::wstring& value = {} );
		HCCFG_EXPORT hcc::Reference<Node> FindByPath( const std::wstring_view& path ) const;
	};




	class Elements : public Container
	{
		template<typename T, NodeType nodeType>
		friend class ValueT;
		friend class Config::Root;
		friend hcc::Reference<Node> Internal::FindByPath( const hcc::Reference<Node>& node, const std::wstring_view& path );
	public:
		using Base = Container;
		static constexpr NodeType NODETYPE = NodeType::Elements;
	private:
		using MutexType = hcc::SlimReaderWriterLock;
		using WriterLock = std::unique_lock<MutexType>;
		using ReaderLock = std::shared_lock<MutexType>;

		mutable MutexType mutex_;
		mutable std::map<std::wstring_view, hcc::Reference<Element> > items_;

		Elements( Node* owner ) noexcept
			: Base( owner, NodeType::Elements, L"Elements" )
		{
		}
	public:
		hcc::Reference<Node> Find( const std::wstring_view& name ) const override
		{
			ReaderLock lock( mutex_ );
			auto it = items_.find( name );
			if ( it != items_.end( ) )
			{
				return it->second;
			}
			return Base::Find( name );
		}

		bool Delete( const std::wstring_view& name )
		{
			hcc::Reference<Element> ref;
			{
				WriterLock lock( mutex_ );
				auto it = items_.find( name );
				if ( it != items_.end( ) )
				{
					ref = it->second;
					items_.erase( it );
				}
			}
			if ( ref )
			{
				ref->DoOnDelete( );
				return true;
			}
			return false;
		}

		HCCFG_EXPORT hcc::Reference<Element> AddElement( const std::wstring_view& name );
		HCCFG_EXPORT hcc::Reference<Node> FindByPath( const std::wstring_view& path ) const;
	};



	class Environment;
	class EnvironmentValue : public ValueBase
	{
		friend class Environment;
	public:
		using Base = ValueBase;
		static constexpr NodeType NODETYPE = NodeType::EnvironmentValue;
	private:
		EnvironmentValue( Node* owner, const NameType& name ) noexcept
			: Base( owner, NodeType::EnvironmentValue, name )
		{ }
		EnvironmentValue( Node* owner, NameType&& name ) noexcept
			: Base( owner, NodeType::EnvironmentValue, std::move( name ) )
		{ }
		EnvironmentValue( Node* owner, const NameViewType& name ) noexcept
			: Base( owner, NodeType::EnvironmentValue, name )
		{ }

	public:
		HCCFG_EXPORT std::wstring Value( ) const;
		HCCFG_EXPORT bool SetValue(const std::wstring& value ) const;
		bool SetValue( const std::string& value ) const
		{
			auto s = hcc::ToWideString( value );
			return SetValue( s );
		}
	};

	class Environment : public Container
	{
		friend class Container;
		friend class Config::Root;
		friend hcc::Reference<Node> Internal::FindByPath( const hcc::Reference<Node>& node, const std::wstring_view& path );
	public:
		using Base = Container;
		static constexpr NodeType NODETYPE = NodeType::Environment;
		struct iLess
		{
			[[nodiscard]] bool operator()( const std::wstring_view& first, const std::wstring_view& second ) const
			{
				auto firstLength = first.length( );
				auto secondLength = second.length( );
				auto compareLength = std::min( firstLength, secondLength );
				auto compareResult = _wcsnicmp( first.data( ), second.data( ), compareLength );
				if ( compareResult != 0 )
				{
					return compareResult < 0;
				}
				else
				{
					return firstLength < secondLength;
				}
			}
		};
		using ContainerType = std::map<std::wstring_view, hcc::Reference<EnvironmentValue>, iLess>;
	private:
		mutable ContainerType items_;
		Environment( Config::Root* root );
		HCCFG_EXPORT void Reload( );

		std::set< std::wstring_view, iLess> InternalKeys( ) const
		{
			std::set< std::wstring_view, iLess>	result;
			for ( const auto& item : items_ )
			{
				result.emplace( item.first );
			}
			return result;
		}

		hcc::Reference<EnvironmentValue> InternalFind( const std::wstring_view& name ) const
		{
			auto it = items_.find( name );
			if ( it != items_.end( ) )
			{
				return it->second;
			}
			return {};
		}
		hcc::Reference<EnvironmentValue> LockedInternalFind( const std::wstring_view& name ) const
		{
			ReaderLock lock( mutex_ );
			return InternalFind( name );
		}
	protected:
		virtual void DoOnDelete( )
		{
			for ( const auto& entry : items_ )
			{
				entry.second->DoOnDelete( );
			}
			Base::DoOnDelete( );
		}
	public:
		const ContainerType& Items( ) const
		{
			// address of items_ is immutable, hence locking makes no sense.
			return items_;
		}

		std::set< std::wstring_view, iLess> Keys( ) const
		{
			ReaderLock lock( mutex_ );
			return InternalKeys( );
		}

		HCCFG_EXPORT hcc::Reference<EnvironmentValue> Read( const std::wstring_view& name ) const;
		hcc::Reference<Node> Find( const std::wstring_view& name ) const override
		{
			return Read( name );
		}
		HCCFG_EXPORT bool Write( const std::wstring_view& name, const std::wstring& value );
		HCCFG_EXPORT bool Delete( const std::wstring_view& name );
		HCCFG_EXPORT hcc::Reference<Node> FindByPath( const std::wstring_view& path ) const;
	};


	class Root : public Container
	{
		friend hcc::Reference<Node> Internal::FindByPath( const hcc::Reference<Node>& node, const std::wstring_view& path );
	public:
		using Base = Container;
		static constexpr NodeType NODETYPE = NodeType::Root;
		mutable hcc::Reference<Config::Elements> elements_;
		mutable hcc::Reference<Config::Environment> environment_;
	private:
		Root( ) noexcept
			: Base(nullptr,NodeType::Root, L"Root" )
		{ }
	public:
		HCCFG_EXPORT ~Root( ) override;
		static HCCFG_EXPORT hcc::Reference<Root> Instance( );
		static HCCFG_EXPORT	void Reset( );
		
		HCCFG_EXPORT hcc::Reference<Node> Find( const std::wstring_view& name ) const override;

		HCCFG_EXPORT const hcc::Reference<Config::Elements>& Elements( ) const;
		HCCFG_EXPORT const hcc::Reference<Config::Environment>& Environment( ) const;

		HCCFG_EXPORT hcc::Reference<Node> FindByPath( const std::wstring_view& path ) const;

	};

	inline Environment::Environment( Config::Root* root )
		: Base( root, NodeType::Environment, L"Environment" )
	{
		Reload( );
	}

	inline hcc::Reference<Config::Root> Node::Root( ) const
	{
		if ( owner_ != nullptr )
		{
			return owner_->Root( );
		}
		return hcc::Reference<Config::Root>(static_cast<Config::Root*>(const_cast<Node*>( this )), true );
	}


}


#endif
