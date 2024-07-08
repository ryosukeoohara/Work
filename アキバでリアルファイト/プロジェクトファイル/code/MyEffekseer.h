//===========================================================
//
// �G�t�F�N�V�A[MyEffekseer.h]
// Author �匴�叫
//
//===========================================================
#ifndef _EFFEKSEER_H_     //���̃}�N������`����ĂȂ�������
#define _EFFEKSEER_H_     //2�d�C���N���[�h��h�~�̃}�N�����`����

#define MAX_EFK   (64)

//===========================================================
// �G�t�F�N�V�A�N���X��`
//===========================================================
class CMyEffekseer
{
public:
	CMyEffekseer();     // �R���X�g���N�^
	~CMyEffekseer();    // �f�X�g���N�^

	// ���
	enum TYPE
	{
		TYPE_NONE = 0,  // �Ȃ���Ȃ�
		TYPE_IMPACT,    // �Ռ��g
		TYPE_HIT,       // �q�b�g
		TYPE_MAX
	};

	// ���
	struct Info
	{
		Effekseer::Vector3D pos;       // �ʒu
		Effekseer::Vector3D rot;       // ����
		Effekseer::Vector3D scale;     // �傫��
		Effekseer::EffectRef effect;   // �G�t�F�N�g
		Effekseer::Handle efkHandle;   // �n���h��
		const char* EfkName;           // ���O
		int32_t time;                  // ����
	};

	void Init(void);                   // ����������
	void Uninit(void);                 // �I������ 
	void Update(void);                 // �X�V����
	void Draw(void);                   // �`�揈��

	// �ݒ�
	void Set(const char* FileName, ::Effekseer::Vector3D pos, ::Effekseer::Vector3D rot, ::Effekseer::Vector3D scale);  // �G�t�F�N�g
	void SetupEffekseerModules(::Effekseer::ManagerRef efkManager);                                                     // ���W���[��

	// �擾
	::EffekseerRendererDX9::RendererRef GetEffekseerRenderer(void) { return m_EfkRenderer; }                            // �G�t�F�N�g�����_���[
	::Effekseer::ManagerRef GetEfkManager(void) { return m_EfkManager; }                                                // �G�t�F�N�g�}�l�[�W��
	

	void Release(int idx);                                   // �w�肵���G�t�F�N�g���I������
	static const char* m_apEfkName[CMyEffekseer::TYPE_MAX];  // �G�t�F�N�g�̖��O

private:

	// �����o�ϐ� 
	Info m_Info[MAX_EFK];
	EffekseerRendererDX9::RendererRef m_EfkRenderer;
	::Effekseer::Matrix44 m_CameraMatrix;
	::Effekseer::Matrix44 m_ProjectionMatrix;
	::Effekseer::ManagerRef m_EfkManager;
	::Effekseer::Vector3D m_ViewerPosition;
	int m_nNum;
};

#endif