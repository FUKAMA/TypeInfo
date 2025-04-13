#pragma once
#include <atomic>
#include <string>
#include <unordered_map>

namespace stl
{
	using TypeID = size_t;

	/// <summary>
	/// コンポーネントの一意なIDを生成、管理するクラス
	/// </summary>
	class TypeIDAllocator
	{
	public:

		template<typename Type>
		TypeID GetID()
		{
			std::string_view keyName = __FUNCSIG__;
			auto itr = m_umNameToTypeID.find(keyName.data());
			if (itr == m_umNameToTypeID.end())
			{
				Allocate(keyName);
				itr = m_umNameToTypeID.find(keyName.data());
			}

			return itr->second;
		}

	private:

		void Allocate(std::string_view a_keyName);



	private:

		std::atomic<TypeID> m_counter = 0;

		std::unordered_map<std::string, TypeID> m_umNameToTypeID;

	};

	template<typename Type>
	class TypeIDContainer
	{
	private:
		template<typename T>
		friend TypeID GetTypeID<T>(TypeIDAllocator* a_pAllocator);

		TypeIDContainer()
		{

		}
	public:

		inline TypeID GetID(TypeIDAllocator* a_pAllocator)
		{
			if (m_id == 0)
			{
				if (a_pAllocator == nullptr)
				{
					return 0;
				}
				m_id = a_pAllocator->GetID<Type>();
			}
			return m_id;
		}

	private:

		TypeID m_id = 0;

	};

	template<typename Type>
	inline static TypeID GetTypeID(TypeIDAllocator* a_pAllocator)
	{
		static TypeIDContainer<Type> idContainer;
		return idContainer.GetID<Type>(a_pAllocator);
	}
}

