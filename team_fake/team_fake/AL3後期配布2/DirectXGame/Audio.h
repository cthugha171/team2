#pragma once
#include<xaudio2.h>
#include<iostream>
#include<fstream>

#pragma comment(lib,"xaudio2.lib")

class XAudio2VoiceCallback :public IXAudio2VoiceCallback
{
	// �{�C�X�����p�X�̊J�n��
	STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};

	// �{�C�X�����p�X�̏I����
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};

	// �o�b�t�@�X�g���[���̍Đ����I��������
	STDMETHOD_(void, OnStreamEnd) (THIS) {};

	// �o�b�t�@�̎g�p�J�n��
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};

	// �o�b�t�@�̖����ɒB������
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext)
	{
		delete[]pBufferContext;
	};

	// �Đ������[�v�ʒu�ɒB������
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};

	// �{�C�X�̎��s�G���[
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
};

class Audio
{
public:
	//�`�����N
	struct Chunk
	{
		char id[4];//�`�����N���Ƃ�ID
		int32_t size;//�`�����N�T�C�Y
	};
	//RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		Chunk chunk;//RIFF
		char type[4];//wave
	};
	//FMT�`�����N
	struct FormatChunk
	{
		Chunk chunk;//fmt
		WAVEFORMAT fmt;//�g�`�t�H�[�}�b�g
	};
	void initialize();
	void PlayWave(const char* filename,float volume=1.0);
	void PlayLoopWave(const char* filename, float volume=1.0);
	void FileOpen();
	void LoadWavFile();
	void Discard();

	void setVolume(float volume);

	float FadeIN(float TargetVolume, float DeltaTime);
	void UpdateFade(float TargetVolume, float TargetTime,float DeltaTime);
	bool endAudioCheck();

	IXAudio2SourceVoice* pSourcVoice = nullptr;
private:
	IXAudio2* pXAudio2 = nullptr;
	UINT32 flags = 0;

	//�}�X�^�[�{�C�X
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;
	//�\�[�X�{�C�X
	
	std::ifstream file;
	const char* filename;
	FormatChunk format;
	Chunk data;
	char* pBuffer;
	XAudio2VoiceCallback voiceCallback;
	float TargetVolume;
};

