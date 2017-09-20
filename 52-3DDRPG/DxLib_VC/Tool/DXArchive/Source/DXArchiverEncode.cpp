// ============================================================================
//
//			�c�w�`�t�@�C���쐬�\�t�g
//
//	Creator			: �R�c�@�I
//	Creation Date	: 2003/09/13
//	Version			: 1.04
//
// ============================================================================

// include ----------------------------
#include "DXArchive.h"
#include "FileLib.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>

// define -----------------------------
#define VERSION			"1.06"				// �o�[�W����
#define FILETYPE		"dxa"				// �g���q

// code -------------------------------

// ���C���֐�
int main( int argc, char *argv[] )
{
	char SrcPath[256], DestPath[256], *KeyString, *SrcDirectoryPath, *DestFilePath ;
	bool Press ;
	int i ;

	printf( "�c�w�`�t�@�C���ȈՍ쐬�\�t�g  Ver%s\n", VERSION ) ;

	// ���������������w���v���o��
	if( argc == 1 ) goto ERR ;

	Press = true ;
	SrcDirectoryPath = NULL ;
	DestFilePath = NULL ;
	KeyString = NULL ;
	for( i = 1 ; i < argc ; i ++ )
	{
		if( argv[i][0] == '-' && argv[i][1] == 'K' && argv[i][2] == ':' )
		{
			KeyString = argv[i] + 3 ;
		}
		else
		if( argv[i][0] == '-' && argv[i][1] == 'N' && argv[i][2] == 'P' && argv[i][3] == '\0' )
		{
			Press = false ;
		}
		else
		if( SrcDirectoryPath == NULL )
		{
			SrcDirectoryPath = argv[i] ;
		}
		else
		{
			DestFilePath = argv[i] ;
		}
	}

	if( SrcDirectoryPath == NULL )
		goto ERR ;

	// �\�[�X�p�X�̃t���p�X���쐬����
	ConvertFullPath__( SrcDirectoryPath, SrcPath ) ;

	// �o�̓t�@�C���p�X�̍쐬
	{
		if( DestFilePath != NULL )
		{
			char temp[256] ;

			strcpy( temp, DestFilePath ) ;
			ConvertFullPath__( temp, DestPath ) ;
		}
		else
		{
			// �\�[�X�p�X����o�̓t�@�C�������쐬����
			sprintf( DestPath, "%s.%s", SrcPath, FILETYPE ) ;
		}
	}

	// �A�[�J�C�u�t�@�C�����쐬����
	DXArchive::EncodeArchiveOneDirectory( DestPath, SrcPath, Press, KeyString ) ;

	// �I��
	return 0 ;

ERR:

	printf( "DxaEncode.exe [-K:KeyString] [-NP] SrcDirectoryPath  [DestFilePath]\n\n" ) ;
	printf( "�E�c�w�`�t�@�C���ɂ������t�H���_���h���b�O���h���b�v���邾���ł��쐬�\�ł�\n" ) ; 
	printf( "�E-K  �I�v�V�����Ō���ݒ�o���܂�(�ő�P�Q����) �@��  -K:KeyCode \n" ) ; 
	printf( "�E-NP �A�[�J�C�u���Ɉ��k���s��Ȃ�\n" ) ;
	return -1; 
}


