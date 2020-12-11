#pragma once
#include<xaudio2.h>
#include<iostream>
#include<fstream>

#pragma comment(lib,"xaudio2.lib")

class XAudio2VoiceCallback :public IXAudio2VoiceCallback
{
	// ボイス処理パスの開始時
	STDMETHOD_(void, OnVoiceProcessingPassStart) (THIS_ UINT32 BytesRequired) {};

	// ボイス処理パスの終了時
	STDMETHOD_(void, OnVoiceProcessingPassEnd) (THIS) {};

	// バッファストリームの再生が終了した時
	STDMETHOD_(void, OnStreamEnd) (THIS) {};

	// バッファの使用開始時
	STDMETHOD_(void, OnBufferStart) (THIS_ void* pBufferContext) {};

	// バッファの末尾に達した時
	STDMETHOD_(void, OnBufferEnd) (THIS_ void* pBufferContext)
	{
		delete[]pBufferContext;
	};

	// 再生がループ位置に達した時
	STDMETHOD_(void, OnLoopEnd) (THIS_ void* pBufferContext) {};

	// ボイスの実行エラー
	STDMETHOD_(void, OnVoiceError) (THIS_ void* pBufferContext, HRESULT Error) {};
};

class Audio
{
public:
	//チャンク
	struct Chunk
	{
		char id[4];//チャンクごとのID
		int32_t size;//チャンクサイズ
	};
	//RIFFヘッダチャンク
	struct RiffHeader
	{
		Chunk chunk;//RIFF
		char type[4];//wave
	};
	//FMTチャンク
	struct FormatChunk
	{
		Chunk chunk;//fmt
		WAVEFORMAT fmt;//波形フォーマット
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

	IXAudio2SourceVoice* pSourcVoice = nullptr;
private:
	IXAudio2* pXAudio2 = nullptr;
	UINT32 flags = 0;

	//マスターボイス
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;
	//ソースボイス
	
	std::ifstream file;
	const char* filename;
	FormatChunk format;
	Chunk data;
	char* pBuffer;
	XAudio2VoiceCallback voiceCallback;
	float TargetVolume;
};

