#pragma once
#include <atomic>
#include <string>
#include <unordered_map>

namespace stl
{
	// �^���ƂɈ�ӂɊ���U����A�Ԃ�ID��\���^�G�C���A�X
	using TypeID = size_t;

	/// <summary>
	///	�^�̈�ӂ�ID�𐶐��A�Ǘ�����N���X
	/// �S�Ă̖|��P�ʂŋ��ʂ̃C���X�^���X���g�p���邱�Ƃœ���ID���g�p���邱�Ƃ��ł���
	/// </summary>
	class TypeIDAllocator
	{
	public:

		/// <summary>
		/// ��ӂȌ^ID���R���e�i����擾����
		/// �܂���������ĂȂ���ΐ������ăR���e�i�ɒǉ�����
		/// </summary>
		/// <typeparam name="Type"></typeparam>
		/// <returns></returns>
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

		/// <summary>
		/// �V�����^ID�𐶐����ēo�^����
		/// </summary>
		/// <param name="a_keyName">�^���ƂɓW�J�����֐����̕�����</param>
		void Allocate(std::string_view a_keyName);



	private:

		std::atomic<TypeID> m_counter = 0;

		std::unordered_map<std::string, TypeID> m_umNameToTypeID;

	};

	/// <summary>
	/// �R���p�C������GetTypeID�֐����ŃC���X�^���X���쐬����A
	/// �^���ƂɈ�ӂ�ID���i�[����N���X
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	template<typename Type>
	class TypeIDContainer
	{
	private:
		template<typename T>
		friend TypeID GetTypeID(TypeIDAllocator& a_allocator);

		TypeIDContainer()
		{

		}
	public:

		/// <summary>
		/// ���̃R���e�i���Ǘ�����^ID��Ԃ�
		/// �^ID������U���ĂȂ���΁A�����̃A���P�[�^����ID���󂯎��
		/// </summary>
		/// <param name="a_allocator"></param>
		/// <returns></returns>
		inline TypeID GetID(TypeIDAllocator& a_allocator)
		{
			if (m_id == 0)
			{
				m_id = a_allocator.GetID<Type>();
			}
			return m_id;
		}

	private:

		TypeID m_id = 0;

	};

	/// <summary>
	/// �^���ƂɈ�ӂŘA�Ԃ�ID�𐶐�����֐�
	/// ����TypeIDAllocator�̃C���X�^���X���g�����ƂňقȂ�|��P�ʊԂŋ��ʂ̌^ID���g�����Ƃ��ł���
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <param name="a_pAllocator"></param>
	/// <returns></returns>
	template<typename Type>
	inline static TypeID GetTypeID(TypeIDAllocator& a_allocator)
	{
		static TypeIDContainer<Type> idContainer;
		return idContainer.GetID(a_allocator);
	}
}

