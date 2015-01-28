// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIVERTEXBUFFER_H
#define	MOAIVERTEXBUFFER_H

#include <moai-sim/MOAIGfxBuffer.h>
#include <moai-sim/MOAIGfxResource.h>

class MOAIVertexFormat;

//================================================================//
// MOAIVbo
//================================================================//
class MOAIVbo {
public:

	u32		mVAO; // vertex array
	u32		mVBO; // vertex buffer
};

//================================================================//
// MOAIVertexBuffer
//================================================================//
/**	@lua	MOAIVertexBuffer
	@text	Vertex buffer class.
*/
class MOAIVertexBuffer :
	public MOAIGfxBufferBase,
	public ZLByteStream {
private:

	static const u32 NULL_FORMAT = 0xffffffff;

	u32										mDefaultFormat;
	MOAILuaSharedPtr < MOAIVertexFormat >	mFormat;

	ZLLeanArray < u8 >			mBuffer;
	
	ZLLeanArray < MOAIVbo >		mVBOs;
	u32							mCurrentVBO;
	u32							mHint;
	
	bool						mIsDirty;
	bool						mUseVBOs;
	
	//----------------------------------------------------------------//
	static int		_bless					( lua_State* L );
	static int		_release				( lua_State* L );
	static int		_reserve				( lua_State* L );
	static int		_reserveVBOs			( lua_State* L );
	static int		_reserveVerts			( lua_State* L );
	static int		_reset					( lua_State* L );
	static int		_setFormat				( lua_State* L );
	static int		_writeColor32			( lua_State* L );

	//----------------------------------------------------------------//
	u32				GetLoadingPolicy		();
	bool			OnCPUCreate				();
	void			OnCPUDestroy			();
	void			OnGPUBind				();
	bool			OnGPUCreate				();
	void			OnGPUDestroy			();
	void			OnGPULost				();
	void			OnGPUUnbind				();
	
public:
	
	DECL_LUA_FACTORY ( MOAIVertexBuffer )
	
	GET ( const ZLBox&, Bounds, mBounds )
	GET ( u32, VertexCount, mTotalElements )
	
	//----------------------------------------------------------------//
	void						Bless					();
	void						Clear					();
	size_t						GetSize					();
	const MOAIVertexFormat*		GetVertexFormat			() const;
								MOAIVertexBuffer		();
								~MOAIVertexBuffer		();
	void						RegisterLuaClass		( MOAILuaState& state );
	void						RegisterLuaFuncs		( MOAILuaState& state );
	void						Reserve					( u32 size );
	void						ReserveVBOs				( u32 gpuBuffers );
	void						SerializeIn				( MOAILuaState& state, MOAIDeserializer& serializer );
	void						SerializeOut			( MOAILuaState& state, MOAISerializer& serializer );
};

#endif
