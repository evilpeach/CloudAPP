#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Light.h"
#include "cinder/CameraUi.h"
#include "cinder/Camera.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CloudAPPApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

  private:
	  int			width;
	  int			 height;	
	  CameraPersp	 mCamera;
	  CameraUi		 mCamUi;
	  Light			mlight;
	  vec3			mLightPos;
	  float			time;
	  vec2 mousePos;
	
	gl::GlslProgRef	mShaderCloud;
	gl::TextureRef	noise;

	vec3 mCubePos, mCubeSize;
	gl::BatchRef	mBatchGBufferBox;
};

void CloudAPPApp::setup()
{
	/*
	mCamera = CameraPersp(getWindowWidth(), getWindowHeight(), 60.0f);
	mCamera.lookAt(vec3(0, 0, -200), vec3(0, 0, 0));
	mCamUi = CameraUi(&mCamera, getWindow(), -1);*/

	width = getWindowWidth();
	height = getWindowHeight();
	time = getElapsedSeconds();

	mLightPos.x = getMousePos().x;
	mLightPos.y = getMousePos().y;
	mLightPos.z = 200.0f;

	noise = gl::Texture::create(loadImage(loadAsset("noise.png")));
	mShaderCloud = gl::GlslProg::create(loadAsset("cloud.vert"), loadAsset("cloud.frag"));

}

void CloudAPPApp::mouseDown( MouseEvent event )
{
	mousePos = event.getPos();
}

void CloudAPPApp::update()
{

}

void CloudAPPApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 

	gl::ScopedGlslProg shader(mShaderCloud);

	mShaderCloud->uniform("iGlobalTime", time);
	mShaderCloud->uniform("iMouse", mousePos);
	mShaderCloud->uniform("iResolution", vec2(width, height));
	mShaderCloud->uniform("iChannel0", 0); // use texture unit 0

	//app::console() << width << "   " << height << endl;

	// draw image
	gl::ScopedTextureBind iChannel0(noise);
	gl::drawSolidRect(getWindowBounds());

	//mBatchGBufferBox->draw();

	//gl::color(Color::white());
	//gl::drawCube(mCubePos, mCubeSize);


}

CINDER_APP( CloudAPPApp, RendererGl )
