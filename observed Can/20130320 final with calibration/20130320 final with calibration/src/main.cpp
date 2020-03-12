#include <Ogre.h>
#include <OgreTextAreaOverlayElement.h>
#include <ExampleApplication.h>
#include "Hydrax/Hydrax.h"
#include "Hydrax/Noise/Perlin/Perlin.h"
#include "Hydrax/Modules/ProjectedGrid/ProjectedGrid.h"
#include "SamplePlugin.h"
#include <irrKlang.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>
#include<string.h>
#include <sstream>
#include "demoNetwork.h" 
using namespace irrklang;
using namespace std;
#define _def_SkyBoxNum 3

//-------------------------------------------Adding sound library---------------------------------------------------------------//
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

 ISoundEngine* engine ;
 ISound* music;
 ISoundEngine* engineExplosion ;
 ISound* musicExplosion;

 //ISoundEngine1* engine1 ;
 //ISound1* music1;
 //ISoundEngine1* engineExplosion1 ;
 //ISound1* musicExplosion1;


//----------------------------------------------------- Hydrax pointer------------------------------------------------------------//
Hydrax::Hydrax *mHydrax = 0;
Ogre::String mSkyBoxes[_def_SkyBoxNum] ={"Sky/ClubTropicana","Sky/EarlyMorning","Sky/Clouds"};
Ogre::Vector3 mSunPosition[_def_SkyBoxNum] = 
{Ogre::Vector3(0,10000,0),
Ogre::Vector3(0,0,90000),
Ogre::Vector3(0,10000,0)};

Ogre::Vector3 mSunColor[_def_SkyBoxNum] = 
{Ogre::Vector3(1, 0.9, 0.6),
Ogre::Vector3(0,0,0),
Ogre::Vector3(0.45,0.45,0.45)};
int mCurrentSkyBox = 0;
Ogre::Vector3 camPos1;
bool suvi;

//------------------------------------------- Just to wshow skyboxes information---------------------------------------------------//
Ogre::TextAreaOverlayElement* mTextArea = 0;
Ogre::TextAreaOverlayElement* mTextArea55 = 0;
Ogre::TextAreaOverlayElement* mTextArea56 = 0;
const unsigned int NUM_FISH=30;
const unsigned int NUM_FISH_WAYPOINTS=9000;
const unsigned int FISH_PATH_LENGTH=280000; 
const Real FISH_SCALE=1;
std::vector<Entity*> mSurfaceEnts;
std::vector<Entity*> mSubmergedEnts;
RenderTarget* mRefractionTarget;
RenderTarget* mReflectionTarget;
Plane mWaterPlane;
Entity* mWater;
std::vector<SceneNode*> mFishNodes;
std::vector<AnimationState*> mFishAnimStates;
std::vector<SimpleSpline> mFishSplines;	
Real mFishAnimTime;
const unsigned int NUM_FISH1=2;
const unsigned int NUM_FISH_WAYPOINTS1=19000;
const unsigned int FISH_PATH_LENGTH1=290000; 
const Real FISH_SCALE1=2;
std::vector<Entity*> mSurfaceEnts1;
std::vector<Entity*> mSubmergedEnts1;
RenderTarget* mRefractionTarget1;
RenderTarget* mReflectionTarget1;
Plane mWaterPlane1;
Entity* mWater1;
std::vector<SceneNode*> mFishNodes1;
std::vector<SimpleSpline> mFishSplines1;
std::vector<AnimationState*> mFishAnimStates1;		
Real mFishAnimTime1;
SceneNode* mPivot;
SceneNode *enemycraftposition;
SceneNode* expboat;
Entity* expboat1;
Entity* ent94;
SceneNode* ship94;
Entity* ent95;
SceneNode* ship95;
SceneNode *mFountainNode1; 
SceneNode* fNode1;
SceneNode *mFountainNode2;
SceneNode* fNode2;
Ogre::Vector3 joyshipPos(800,25,-980);

SceneNode *BulletTemp; 
SceneNode *GYawNodeT;
SceneNode *GPitchNodeT;
SceneNode *HeadNodeT;

Ogre::Real mDistance;                  
Ogre::Vector3 mDirection;              
Ogre::Vector3 mDestination;            
Ogre::AnimationState *mAnimationState; 
Ogre::Entity *mEntity;                 
Ogre::SceneNode *mNode;                
std::deque<Ogre::Vector3> mWalkList;   
Ogre::Real mWalkSpeed;                 
Ogre::SceneNode *HeadNode;
Ogre::SceneNode *GunNode;
Ogre::SceneNode *GYawNode;
Ogre::SceneNode *GPitchNode;
Entity* GPitchNode1;
SceneNode *Bullet;
Entity* DVBullet;
SceneNode *tempBullet;
int inc=0;
// int inc=0;
Ogre::Vector3 bulpos;
SceneNode *mFountainNode3; 
SceneNode* fNode3;
AxisAlignedBox aab;
AxisAlignedBox aab1;
int hitcounter=0;
int numenemy=0;
int Collisionship;
AxisAlignedBox aab3;
int shiphitter=0;
DWORD sTime = GetTickCount();
Ogre::SceneNode *cameraNode;
bool fNode;
string Result;

int fireTime=0;
float pitchval=0.4;
float rollval=0.04;

time_t now;
struct tm *current;
int min1=100;
int endtick;
Billboard* mRedLightBoard;

Real GunUpTOLD=500;
Real GunRightHOLD=15;
Real xtranslate=0;
Real TrAngle = 0;
Real TrSetAngle = 0;
Real CalibCorrection =0;


//--------------------------------------------------ExampleFrameListener class-------------------------------------------------//


// VSC - this function is set to update the strength of the waves
void changeStrength(float step)
{
	// VSC -  mHydrax is of course your Hydrax pointer
	Hydrax::Module::ProjectedGrid* module = static_cast<Hydrax::Module::ProjectedGrid*>(mHydrax->getModule());
	Hydrax::Module::ProjectedGrid::Options options = module->getOptions();
	options.Strength = step;
	module->setOptions(options);
}

// VSC - this function is set to update the choppystrength of the waves
void changeChoppyStrength(float step)
{

	Hydrax::Module::ProjectedGrid* module = static_cast<Hydrax::Module::ProjectedGrid*>(mHydrax->getModule());
	Hydrax::Module::ProjectedGrid::Options options = module->getOptions();
	options.ChoppyStrength=step;
	module->setOptions(options);
}

// VSC - this function is set to update the choppy smoothness of the waves
void changeChoppySmooth(int step)
{

	Hydrax::Module::ProjectedGrid* module = static_cast<Hydrax::Module::ProjectedGrid*>(mHydrax->getModule());
	Hydrax::Module::ProjectedGrid::Options options = module->getOptions();
	if(step=1){
		options.ChoppyWaves=true;
	}
	else{
		options.ChoppyWaves=false;
	}

	module->setOptions(options);
}


// VSC - this function is set to update the Elevation of the waves
void changeElevation(float step)
{

	Hydrax::Module::ProjectedGrid* module = static_cast<Hydrax::Module::ProjectedGrid*>(mHydrax->getModule());
	Hydrax::Module::ProjectedGrid::Options options = module->getOptions();

	options.Elevation=step;

	module->setOptions(options);
}



// VSC - this function is set to update the smoothness of the waves
void changeSmooth(int step)
{

	Hydrax::Module::ProjectedGrid* module = static_cast<Hydrax::Module::ProjectedGrid*>(mHydrax->getModule());
	Hydrax::Module::ProjectedGrid::Options options = module->getOptions();
	if(step==1){
		options.Smooth=true;
	}
	else{
		options.Smooth=false;
	}

	module->setOptions(options);
}

// VSC - this function is set to update the complexity of the waves
void changeComplexity(float strength)
{


	Hydrax::Module::ProjectedGrid* module = static_cast<Hydrax::Module::ProjectedGrid*>(mHydrax->getModule());
	Hydrax::Module::ProjectedGrid::Options options = module->getOptions();
	options.Complexity=strength;
	module->setOptions(options);


}

	float complexity=0;
		float elevation=150;
		float choppy=3.2;
		float strength=50;
		bool smooth=false;
		bool choppysmooth=false;

class ExampleHydraxDemoListener : public ExampleFrameListener
{	
public:
DemoNet* net;
 Ogre::SceneNode *cameraYawNode;
 Ogre::SceneNode *cameraPitchNode;
 Ogre::SceneNode *cameraRollNode;
 SceneManager *mSceneMgr;
 Real mKeyBuffer;


    ExampleHydraxDemoListener(RenderWindow* win, Camera* cam, SceneManager *sm)
            : ExampleFrameListener(win,cam)
            , mSceneMgr(sm)
            , mKeyBuffer(-1)
    {
		net = new DemoNet();
    }

	bool nextLocation(void){

		if (mWalkList.empty())
        return false;

		mDestination = mWalkList.front();  // this gets the front of the deque
        mWalkList.pop_front();             // this removes the front of the deque
 
        mDirection = mDestination - mNode->getPosition();
        mDistance = mDirection.normalise();


	    return true;
	}


//----------------------------------------------framestarted---------------------------------------------------------------//
	double s;
	int pp;
	DWORD nowticks;
	
    bool frameStarted(const FrameEvent &e)
    {

		 

//--------------------------------------------gun firing-----------------------------------1200,360   335,3600//
		

if(isStarted != true){
			Ogre::LogManager::getSingleton().logMessage("Switching to another thread\n");
			SwitchToThread();
			Ogre::LogManager::getSingleton().logMessage("IN IF\n");
			return true;
		}

else{
	//Real MoveFactor = /*(jmove/5)*/100  * e.timeSinceLastFrame;
	Real ShipK,ShipI,ShipL,ShipJ,GunUpT,GunDownG,GunRightH,GunRightHH,GunLeftB,GunShot1;
		 Real GunDistance=100;
			Ogre::LogManager::getSingleton().logMessage("IN ELSE\n");
			EnterCriticalSection( &cs );
			//cout<<"****************************************************%%"<<*(values)<<"\n";
			// cout<<"****************************************************%%"<<*(values+1)<<"\n";
			 // cout<<"****************************************************%%"<<*(values+2)<<"\n";
			 //  cout<<"****************************************************%%"<<*(values+3)<<"\n";
			   // cout<<"****************************************************%%"<<*(values+4)<<"\n";
			GunShot1=*(values+4);
			ShipI=*(values+2);
			ShipJ=*(values+3);
			GunUpT=*(values+1);
		    GunRightH=*(values);
			TrAngle = *(values);
			
			//GunRightH=GunRightH;
			//GunUpT=GunUpT;
			//GunUpTOLD=GunUpT;
			//GunRightHOLD=GunRightH;
			cout<<"****************************************************%$%"<<GunRightH<<"\n";
			cout<<"****************************************************%$%"<<GunUpT<<"\n";
			cout<<"****************************************************%$%"<<GunShot1<<"\n";
			cout<<"****************************************************%$%"<<ShipI<<"\n";
			cout<<"****************************************************%$%"<<ShipJ<<"\n";
			cout<<"**************************$$$$$$$$$$$*********************"<<CalibCorrection<<"\n";
			

			/*if(abs(GunUpTOLD-GunUpT)>10||abs(GunRightHOLD-GunRightH)>10){
			
	        GunUpTOLD=GunUpT;
			GunRightHOLD=GunRightH;

			//GunUpT=GunUpTOLD-GunUpT;
			//GunRightH=GunRightHOLD2-GunRightH;
		
		
				}else{
			
				
				GunUpT=0;
				GunRightH=0;
			
				}
				
			if(GunRightH>18)
				GunRightH=-0.4;else if(GunRightH<0)GunRightH=0.4;
				else GunRightH=0;


					if(GunUpT>500)
				GunUpT=-0.2;else if(GunUpT<490)GunUpT=0.2;
				else GunUpT=0;
			cout<<"****************************************************%%"<<GunRightH<<"\n";
			cout<<"****************************************************%%"<<GunUpT<<"\n";
			*/


		    //cout<<"****************************************************%%"<<*(values+4)<<"\n";
	/*		if(*values==65){
			musicExplosion = engine->play3D("../../media/gunfire.wav",vec3df(0,0,0), false, false, false);
	tempBullet->setPosition(HeadNode->getPosition().x,HeadNode->getPosition().y+5,HeadNode->getPosition().z);
	tempBullet->setOrientation(GPitchNode->getOrientation());
			}*/
			
			///////////////////////////
			

		nowticks = GetTickCount() / 358;
		pp=(nowticks-sTime);
		s=pp%3817;

now = time(0);
current = localtime(&now);


//cout << "hour: " << current->tm_hour << endl;
cout << "mins: " << current->tm_min << endl;
endtick=current->tm_min-min1;
				if(endtick>=2||endtick==-56){
mTextArea55->setCaption("   Session Completed\n"+ Result+ " Enemy Boats Destroyed");

}
LeaveCriticalSection( &cs );

//cout << "MyVals: "<< ShipK << "," << ShipI << "," <<ShipL << "," << ShipJ<< "," << GunUpT << "," <<GunDownG<< "," <<GunRightH<< "," <<GunLeftB<< "," <<GunShot1<< "\n";




//cout << "sec: " << current->tm_sec << endl;
		
//long before =GetTickCount();
//long k = GetTickCount()-before;
//
//cout << "mins: " << k << endl;

		Real MoveFactor = 240.0 * e.timeSinceLastFrame;
		Real AnimFactor	= 50000*e.timeSinceLastFrame;

		// Check camera height
		//Ogre::RaySceneQuery *raySceneQuery =mSceneMgr->createRayQuery(Ogre::Ray(mCamera->getPosition() + Ogre::Vector3(0,1000000,0),Vector3::NEGATIVE_UNIT_Y));
		//Ogre::RaySceneQueryResult& qryResult = raySceneQuery->execute();
  //      Ogre::RaySceneQueryResult::iterator i = qryResult.begin();
  //      if (i != qryResult.end() && i->worldFragment)
  //      {
		//	if (mCamera->getPosition().y < i->worldFragment->singleIntersection.y + 30)
		//	{
  //              mCamera->setPosition(mCamera->getPosition().x,i->worldFragment->singleIntersection.y + 30,mCamera->getPosition().z);
		//	}
  //      }

		//delete raySceneQuery;
		// Update Hydrax
        mHydrax->update(e.timeSinceLastFrame);
		// Check for skyboxes switch
        mKeyboard->capture();

        if (mKeyboard->isKeyDown(OIS::KC_M) && mKeyBuffer < 0)
        {
			mCurrentSkyBox++;
			if(mCurrentSkyBox > (_def_SkyBoxNum-1))
			{
			    mCurrentSkyBox = 0;
			}

			changeSkyBox();

			mKeyBuffer = 0.5f;
		}

//-----------------------------------------------------ship moving-------------------------------------------------------------------//
		//HeadNode->translate(0.0,std::sin(s)*pitchval,0.0,Node::TS_LOCAL);
		//HeadNode->roll(Ogre::Degree(std::sin(s)*0.03));
		cameraNode->roll(Ogre::Degree(std::sin(s)*rollval));
		cameraNode->pitch(Ogre::Degree(std::sin(s)*rollval));

// Move ship upwards along to world's Y-axis.
		if(ShipI!=0){
//if(mKeyboard->isKeyDown(OIS::KC_I))
	//HeadNode->translate(0.0,0.0,MoveFactor,Node::TS_LOCAL);



 
// Move ship downwards along to world's Y-axis.
//if(mKeyboard->isKeyDown(OIS::KC_K)){
//music = engineExplosion->play3D("../../media/engine.wav",vec3df(0,0,0), false, false, false);
//HeadNode->translate(0.0,0.0,-MoveFactor,Node::TS_LOCAL);
HeadNode->translate(0.0,0.0,3*ShipI,Node::TS_LOCAL);
}

// Move ship left.
if(ShipJ!=0){
	//if(mKeyboard->isKeyDown(OIS::KC_J)){
HeadNode->yaw(Ogre::Degree( ( (ShipJ*3)/100)  ),Node::TS_LOCAL);
GYawNode->yaw(Ogre::Degree( ( (ShipJ*3)/100)  ),Node::TS_LOCAL);
GPitchNode->yaw(Ogre::Degree( ( (ShipJ*3)/100)  ),Node::TS_LOCAL);
//Bullet->setOrientation(HeadNode->getOrientation());

//HeadNode->yaw(Ogre::Degree(0.30),Node::TS_LOCAL);
//GYawNode->yaw(Ogre::Degree(0.30),Node::TS_LOCAL);
//GPitchNode->yaw(Ogre::Degree(0.30),Node::TS_LOCAL);
//Bullet->setOrientation(HeadNode->getOrientation());

}
 
// Move ship right.
/*if(mKeyboard->isKeyDown(OIS::KC_L)){
HeadNode->yaw(Ogre::Degree(-0.3),Node::TS_LOCAL);
GYawNode->yaw(Ogre::Degree(-0.3),Node::TS_LOCAL);
GPitchNode->yaw(Ogre::Degree(-0.3),Node::TS_LOCAL);
//Bullet->setOrientation(HeadNode->getOrientation());
}*/




 //----------------------------------------------------gun camera---------------------------------------------------------------------//

// Rotate gun camera left.
//if(mKeyboard->isKeyDown(OIS::KC_B)){
//GYawNode->yaw(Ogre::Degree(0.8),Node::TS_LOCAL);
//GPitchNode->yaw(Ogre::Degree(0.8),Node::TS_LOCAL);
//}
 
// Rotate gun camera right.
//if(mKeyboard->isKeyDown(OIS::KC_H)){
	if(GunRightH!=0){
		
//GYawNode->yaw(Ogre::Degree( ( (GunUpT*3)/100)  ),Node::TS_LOCAL);
//GPitchNode->yaw(Ogre::Degree( ( (GunUpT*3)/100)  ),Node::TS_LOCAL);

}

// Rotate gun camera upwards.
//if(mKeyboard->isKeyDown(OIS::KC_T))
	if(GunUpT!=0)
//GPitchNode->pitch(Ogre::Degree( ( (GunUpT*3)/2000)  ),Node::TS_LOCAL);
	
// Rotate gun camera downwards.
//if(mKeyboard->isKeyDown(OIS::KC_G))
//GPitchNode->pitch(Ogre::Degree(-0.5),Node::TS_LOCAL);


if(GunShot1==1){
//if(mKeyboard->isKeyDown(OIS::KC_1)){
	engine->setSoundVolume(0.7);

	musicExplosion = engine->play3D("../../media/gunfire.wav",vec3df(0,0,0), false, false, false);
	
	//GunUpT=(GunUpT*0.2);
    //GunRightH=0;//(GunRightH*0.2);

	tempBullet->setPosition(HeadNode->getPosition().x,HeadNode->getPosition().y ,HeadNode->getPosition().z);
	tempBullet->setOrientation(GYawNode->getOrientation());
	tempBullet->setOrientation(GPitchNode->getOrientation());
	//tempBullet->setOrientation(HeadNode->getOrientation());
	
	//Bullet->setOrientation(GPitchNode->getOrientation());
	//Bullet->setOrientation(GYawNode->getOrientation());
	inc=1;
	//GunRightHH=-GunRightH;
	TrSetAngle = TrAngle-CalibCorrection;
	

}else 
{

}




	


if(mKeyboard->isKeyDown(OIS::KC_2)){
	
						strength=20;
						choppy=3.75;
						elevation=50;
						complexity=275;
						 smooth=true;
						 choppysmooth=true;

			changeStrength(strength);

			changeChoppyStrength(choppy);

			changeElevation(150);
			
			changeComplexity(complexity);

			changeSmooth(smooth);
			pitchval=0.65;
			rollval=0.066;

}
if(mKeyboard->isKeyDown(OIS::KC_3)){

						strength=60;
						choppy=3.75;
						elevation=60;
						complexity=264;
						 smooth=true;
						 choppysmooth=true;

						 			changeStrength(strength);

			changeChoppyStrength(choppy);

			changeElevation(150);
			
			changeComplexity(complexity);

			changeSmooth(smooth);

			pitchval=0.85;
			rollval=0.086;

}
if(mKeyboard->isKeyDown(OIS::KC_4)){
	
						strength=100;
						choppy=2.85;
						elevation=40;
						complexity=264;
						 smooth=true;
						 choppysmooth=true;

						 			changeStrength(strength);

			changeChoppyStrength(choppy);

			changeElevation(150);
			
			changeComplexity(complexity);

			changeSmooth(smooth);

			pitchval=1.05;
			rollval=0.09;
}

 
			if(mKeyboard->isKeyDown(OIS::KC_7)){
			CalibCorrection =GunRightH;	
			
			}

			cout<<"**************************$$$$$$$$$$$*********************"<<CalibCorrection<<"\n";
//........................................Callibreate correction............................//



if(inc>=1)
{
	//tempBullet->translate(0.0,0.0,-AnimFactor,Node::TS_LOCAL);
	
	
	xtranslate= AnimFactor * 0.5 * (TrSetAngle /85);
	//xtranslate=-AnimFactor *0.5;
	tempBullet->translate(xtranslate,0.0,-AnimFactor,Node::TS_LOCAL);
//				
//				bulpos=Bullet->getPosition();}				
//
		xtranslate = 0;
	if(inc==5000)
				{
					//Bullet->setVisible(false);
					//fNode3->setVisible(true);
					//mFountainNode3->setVisible(true);

					inc=0;


				}
				
				inc++;
}


 
//---------------------------------------------- Move ship hight------------------------------------------------------------//
	 
if(mKeyboard->isKeyDown(OIS::KC_UP))
this->mTranslateVector.z = -(this->mMoveScale);
 
// Move camera backward.
if(mKeyboard->isKeyDown(OIS::KC_DOWN))
this->mTranslateVector.z = this->mMoveScale;
 
 
 
//-----------------------------------------------------------ship extra---------------------------------------------------------//
 

		

//------------------------------------------------Bullet collision with the ships----------------------------------------------------//

//aab = tempBullet->_getWorldAABB().intersection(ship94->_getWorldAABB());
//			if(!aab.isNull())
//			{
//				
//				hitcounter++;
//				if(hitcounter==5){
//					std::cout<<"blasttttt......hureeeeeeeeeeee";
//					////Explosion emitor setup//////////////////////////
//					mFountainNode1->setPosition(enemycraftposition->getPosition());
//					
//					mFountainNode1->setVisible(false);
//					musicExplosion = engine->play3D("../../media/explosion.wav",vec3df(0,0,0), false, false, false);
//					//////////////////////////////////////////////////////////
//					fNode1->setVisible(true);
//					tempBullet->setPosition(GPitchNode->getPosition());
//					tempBullet->setVisible(true);
//					//ship94->setVisible(false);
//					inc=0;
//				hitcounter=0;
//				aab.setNull();
//				}
//				
//			}		
//
//
//		
//						if(hitcounter>=0)
//			   {
//				ship94->setPosition(joyshipPos.x,joyshipPos.y,joyshipPos.z);
//				//ship94->roll(Degree(-0.000000000000000500));
//				//hitcounter++;
//				if(hitcounter==5)
//				{
//					ship94->setPosition(joyshipPos.x,joyshipPos.y-0.05,joyshipPos.z);
//					//ship94->setPosition(-40,30,40);
//					ship94->roll(Degree(-0.01));
//					fNode1->setVisible(true);
//					mFountainNode1->setVisible(false);
//					hitcounter=0;
//				}
//
//						}



//////-------------------------------------------------------------hit ship----------------------------------------------------------------------//




//--------------------------------------------------------------ship and dovra mooving -------------------------------------------------------//


		mFishAnimTime += e.timeSinceLastFrame;
        while (mFishAnimTime >= FISH_PATH_LENGTH) mFishAnimTime -= FISH_PATH_LENGTH;

        for (unsigned int i = 0; i < NUM_FISH; i++)
        {   //musicExplosion = engine->play3D("../../media/engine.wav",vec3df(0,0,0), false, false, false);






			
			Vector3 lastPos = mFishNodes[i]->getPosition();
            mFishNodes[i]->setPosition(mFishSplines[i].interpolate(mFishAnimTime / FISH_PATH_LENGTH));
			mFishNodes[i]->setDirection(mFishNodes[i]->getPosition() - lastPos, Node::TS_PARENT, Vector3::NEGATIVE_UNIT_X);
			//mFishNodes[i]->yaw( Ogre::Degree(-90));
			mFishNodes[i]->setFixedYawAxis(true);

if(mKeyboard->isKeyDown(OIS::KC_9)){
min1=current->tm_min;
mTextArea55->setCaption("");
numenemy=0;
HeadNode->setPosition(HeadNodeT->getPosition());
HeadNode->setOrientation(HeadNodeT->getOrientation());
Bullet->setPosition(BulletTemp->getPosition());
Bullet->setOrientation(BulletTemp->getOrientation());
GYawNode->setPosition(GYawNodeT->getPosition());
GYawNode->setOrientation(GYawNodeT->getOrientation());
GPitchNode->setPosition(GPitchNodeT->getPosition());
GPitchNode->setOrientation(GPitchNodeT->getOrientation());


HeadNode->setPosition(-4500, 147, 5000);
mFishNodes[i]->setVisible(true);
fNode1->setVisible(false);


}

if(mKeyboard->isKeyDown(OIS::KC_0)){
suvi=false;
HeadNode->setPosition(-4500, 147, 5000);
mTextArea55->setCaption("");
mFishNodes[i]->setVisible(true);
fNode1->setVisible(false);
}

        /*BillboardSet* lightbillboardset = mSceneMgr->createBillboardSet("lightbbs", 1);
		lightbillboardset->setMaterialName("Examples/Flare");
		Billboard* lightbillboard = lightbillboardset->createBillboard(0,0,0,ColourValue(0.5,0.3,0.0f));
		mFishNodes[i]->attachObject(lightbillboardset);
		Vector3 redLightPosition(3150,4950,-27500);
		mRedLightBoard = lightbillboardset->createBillboard(redLightPosition);
		mRedLightBoard->setColour(ColourValue::Black);
		mFishNodes[i]->attachObject(mRedLightBoard);*/
		//mRedYellowLightsNode->attachObject(mRedYellowLights);



	//Ogre::ParticleSystem* thrusters = mSceneMgr->createParticleSystem(25);
 //   thrusters ->setMaterialName("Examples/Flare");
 //   thrusters ->setDefaultDimensions(25, 25);

 //   for (unsigned int b = 0; b < 2; b++)
 //   {
 //           Ogre::ParticleEmitter* emitter = thrusters ->addEmitter("Point");  // add a point emitter

 //           // set the emitter properties
 //           emitter->setAngle(Ogre::Degree(10));
	//		
 //           emitter->setTimeToLive(0.00001);
 //           emitter->setEmissionRate(500);
 //           emitter->setParticleVelocity(5);
 //           emitter->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
	//		emitter->setColour(Ogre::ColourValue::Red, Ogre::ColourValue::Red);
 //           emitter->setPosition(Ogre::Vector3(b == 0 ? 5.7 : -250, 10, 0));
 //   }

	//mFishNodes[i]->createChildSceneNode(Ogre::Vector3(-210, 90, 0))->attachObject(thrusters);

			
			aab1 = expboat->_getWorldAABB().intersection(mFishNodes[i]->_getWorldAABB());
			if(!aab1.isNull()){
				std::cout<<"blasttttt......hureeeeeeeeeeee";
					//mFountainNode1->setPosition(mFishNodes[i]->getPosition());					
					//mFountainNode1->setVisible(false);
					musicExplosion = engine->play3D("../../media/explosion.wav",vec3df(0,0,0), false, false, false);
					fNode=true;
					fNode1->setPosition(mFishNodes[i]->getPosition());
					mFishNodes[i]->setVisible(false);
					//mTextArea55->setCaption("Session Failed !");
					mTextArea55->setCaption("    Session Failed\n" " due to Suicide Attack\n"+ Result+ " Enemy Boats Destroyed");
					min1=current->tm_min;
					camPos1=HeadNode->getPosition();
					suvi=true;
					
					//HeadNode->setPosition(0,-50,0);
					//HeadNode->roll(Degree(-5));


					if(fNode==true){						
			fNode1->setVisible(true);
		}	
					
			}
			if(suvi==true){
						HeadNode->setPosition(camPos1);					
					}
			
			
			aab = tempBullet->_getWorldAABB().intersection(mFishNodes[i]->_getWorldAABB());
			if(!aab.isNull()){
				hitcounter++;
				numenemy++;

				if(hitcounter==1){
					std::cout<<"blasttttt......hureeeeeeeeeeee";
					//mFountainNode1->setPosition(mFishNodes[i]->getPosition());					
					//mFountainNode1->setVisible(false);
					musicExplosion = engine->play3D("../../media/explosion.wav",vec3df(0,0,0), false, false, false);
					//fNode1->setVisible(true);
					fNode=true;
					fNode1->setPosition(mFishNodes[i]->getPosition());
					mFishNodes[i]->setVisible(false);					
									
					tempBullet->setPosition(GPitchNode->getPosition());
					tempBullet->setVisible(true);
					std::cout<<numenemy<<"AAAAAAAAAAAAAAAAA";
					std::stringstream convert;
					convert << numenemy;
					Result = convert.str();
					mTextArea56->setCaption("");

						inc=0;
				    hitcounter=0;
					aab.setNull();
				                 }			
			                 }
				if(fNode==true){
			fNode1->setVisible(true);
		}



        }
		
		
			if(fireTime==300)
			{
				fNode1->setVisible(false);
				fNode1->setPosition(0,-10000,0);
				fireTime=0;
			}
			fireTime++;






			//	mFishAnimTime1 += e.timeSinceLastFrame;
   //     while (mFishAnimTime1 >= FISH_PATH_LENGTH1) mFishAnimTime1 -= FISH_PATH_LENGTH1;

   //     for (unsigned int k = 0; k < NUM_FISH; k++)
   //     {
			////musicExplosion = engine->play3D("../../media/engine.wav",vec3df(0,0,0), false, false, false);
			//Vector3 lastPos = mFishNodes1[k]->getPosition();
   //         mFishNodes1[k]->setPosition(mFishSplines1[k].interpolate(mFishAnimTime1 / FISH_PATH_LENGTH1));
			//mFishNodes1[k]->setDirection(mFishNodes1[k]->getPosition() - lastPos, Node::TS_PARENT, Vector3::NEGATIVE_UNIT_X);
			//mFishNodes1[k]->yaw( Ogre::Degree(-90));
			//mFishNodes1[k]->setFixedYawAxis(true);
   //     }

		mKeyBuffer -= e.timeSinceLastFrame;
        return true;
		}
    }


//---------------------------------------------------------------------------camera movement----------------------------------------------//





    void changeSkyBox()
    {
        // Change skybox
        mSceneMgr->setSkyBox(true, mSkyBoxes[mCurrentSkyBox], 99999*3, true);

        // Update Hydrax sun position and colour
        mHydrax->setSunPosition(mSunPosition[mCurrentSkyBox]);
        mHydrax->setSunColor(mSunColor[mCurrentSkyBox]);

        // Update light 0 light position and colour
        mSceneMgr->getLight("Light0")->setPosition(mSunPosition[mCurrentSkyBox]);
        mSceneMgr->getLight("Light0")->setSpecularColour(mSunColor[mCurrentSkyBox].x,mSunColor[mCurrentSkyBox].y,mSunColor[mCurrentSkyBox].z);

		// Update text area
		mTextArea->setCaption(" "  + Ogre::StringUtil::split(mSkyBoxes[mCurrentSkyBox],"/")[1] + " (" +Ogre::StringConverter::toString(mCurrentSkyBox+1) + "/3). ");

		// Log
        LogManager::getSingleton().logMessage("Skybox " + mSkyBoxes[mCurrentSkyBox] + " selected. ("+Ogre::StringConverter::toString(mCurrentSkyBox+1)+"/"+Ogre::StringConverter::toString(_def_SkyBoxNum)+")");
    }




	void createCamera(void)
{
    // create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // set its position, direction  
    mCamera->setPosition(Ogre::Vector3(0,10,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    // set the near clip distance
    mCamera->setNearClipDistance(5);
 
    
}

};

/** Just to locate palmiers with a pseudo-random algoritm
 */
float seed_ = 801;
float rnd_(const float& min, const float& max)
{
	seed_ += Ogre::Math::PI*2.8574f + seed_*(0.3424f - 0.12434f + 0.452345f);
	if (seed_ > 10000000000) seed_ -= 10000000000;
	return ((max-min)*Ogre::Math::Abs(Ogre::Math::Sin(Ogre::Radian(seed_))) + min);
}


//--------------------------------------------------------sampleapp class------------------------------------------------------------------//

class SampleApp : public ExampleApplication
{
public:
    // Basic constructor
    SampleApp()
    {}

protected:
	void chooseSceneManager()
    {
        // Create the SceneManager, in this case a generic one
        mSceneMgr = mRoot->createSceneManager("TerrainSceneManager");
    }
	/////////////////////////////////ltte boat//////////////////////////////
	void setupFish()
	{
		mFishNodes.resize(NUM_FISH);
		mFishAnimStates.resize(NUM_FISH);
		mFishSplines.resize(NUM_FISH);

		mFountainNode2 = static_cast<SceneNode*>(mSceneMgr->getRootSceneNode()->createChild());
		ParticleSystem* pSys2 = mSceneMgr->createParticleSystem("fountain2", "Examples/Smoke");
		// Point the fountain at an angle
		fNode2= static_cast<SceneNode*>(mFountainNode2->createChild());
		fNode2->attachObject(pSys2);
		mFountainNode2->setVisible(false);
		fNode2->setVisible(false);





		for (unsigned int i = 0; i < NUM_FISH; i++)
        {
			//mFishNodes[i]=ship94;
			// create fish entity
            Entity* ent = mSceneMgr->createEntity("Fish" + StringConverter::toString(i + 1), "slg.mesh");
			
            mSubmergedEnts.push_back(ent);
			
			// create an appropriately scaled node and attach the entity
			mFishNodes[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode();
			mFishNodes[i]->yaw( Ogre::Degree( 0 ) );
			mFishNodes[i]->setScale(Vector3::UNIT_SCALE * FISH_SCALE);
            mFishNodes[i]->attachObject(ent);






			//mFishNodes[i]->createChildSceneNode();
			//mFishNodes[1]->attachObject(pSys2);

            mFishSplines[i].setAutoCalculate(false);  // save the tangent calculation for when we are all done

            // generate random waypoints for the fish to swim through
            for (unsigned int j = 0; j < NUM_FISH_WAYPOINTS; j++)
            {
                Vector3 pos(Math::SymmetricRandom() * 45500, 65, Math::SymmetricRandom() * 14500);

                if (j > 0)  // make sure the waypoint isn't too far from the last, or our fish will be turbo-fish
                {
					const Vector3& lastPos = mFishSplines[i].getPoint(j - 1);
					Vector3 delta = pos - lastPos;
					if (delta.length() > 6200) pos = lastPos + delta.normalisedCopy() * 6200;
                }

                mFishSplines[i].addPoint(pos);
            }

			// close the spline and calculate all the tangents at once
            mFishSplines[i].addPoint(mFishSplines[i].getPoint(0));
            mFishSplines[i].recalcTangents();
        }

		mFishAnimTime = 0;
	}

	///////////////////////dovra//////////////////
	void setupFish1()
	{
		mFishNodes1.resize(NUM_FISH);
		mFishAnimStates1.resize(NUM_FISH);
		mFishSplines1.resize(NUM_FISH);

		for (unsigned int k = 0; k < NUM_FISH; k++)
        {
			// create fish entity

            Entity* ent1 = mSceneMgr->createEntity("Fish1" + StringConverter::toString(k + 1), "dovra11.mesh");
			
            mSubmergedEnts1.push_back(ent1);
			

			// create an appropriately scaled node and attach the entity
			mFishNodes1[k] = mSceneMgr->getRootSceneNode()->createChildSceneNode();
			
			mFishNodes1[k]->setScale(Vector3::UNIT_SCALE * FISH_SCALE1);
            mFishNodes1[k]->attachObject(ent1);
			


            mFishSplines[k].setAutoCalculate(false);  // save the tangent calculation for when we are all done

            // generate random waypoints for the fish to swim through
            for (unsigned int l = 0; l < NUM_FISH_WAYPOINTS1; l++)
            {
                Vector3 pos(Math::SymmetricRandom() * 45900, 190, Math::SymmetricRandom() * 12000);

                if (l > 0)  // make sure the waypoint isn't too far from the last, or our fish will be turbo-fish
                {
					const Vector3& lastPos = mFishSplines1[k].getPoint(l - 1);
					Vector3 delta = pos - lastPos;
					if (delta.length() > 1200) pos = lastPos + delta.normalisedCopy() * 1200;
                }

                mFishSplines1[k].addPoint(pos);
            }

			// close the spline and calculate all the tangents at once
            mFishSplines1[k].addPoint(mFishSplines1[k].getPoint(0));
            mFishSplines1[k].recalcTangents();
        }

		mFishAnimTime1 = 0;
	}


	void setupContent()
	{     

		//mSceneMgr->setSkyBox(true, "Examples/EveningSkyBox");

		// dim orange ambient and two bright orange lights to match the skybox
		mSceneMgr->setAmbientLight(ColourValue(0.3, 0.2, 0));
		Light* light = mSceneMgr->createLight();
		light->setPosition(2000, 1000, -1000);
		light->setDiffuseColour(1, 0.5, 0);
		light = mSceneMgr->createLight();
        light->setPosition(-2000, 1000, 1000);
		light->setDiffuseColour(1, 0.5, 0);

		mPivot = mSceneMgr->getRootSceneNode()->createChildSceneNode();  // create a pivot node
		mFountainNode1 = static_cast<SceneNode*>(mSceneMgr->getRootSceneNode()->createChild());

		// smoke
		ParticleSystem* pSys1 = mSceneMgr->createParticleSystem("fountain1", "Examples/Smoke");
		// Point the fountain at an angle
		fNode1= static_cast<SceneNode*>(mFountainNode1->createChild());
		fNode1->attachObject(pSys1);
		mFountainNode1->setVisible(false);
		fNode1->setVisible(false);
		//mFountainNode1->setScale(1000,50,20);
		mFountainNode1->setPosition(0,0,-0);
		fNode1->setPosition(0,0,0);
	}
	
void cleanupContent()
	{
		mSurfaceEnts.clear();
		mSubmergedEnts.clear();
		mFishNodes.clear();
		mFishAnimStates.clear();
		mFishSplines.clear();

		mSurfaceEnts1.clear();
		mSubmergedEnts1.clear();
		mFishNodes1.clear();
		mFishAnimStates1.clear();
		

		MeshManager::getSingleton().remove("water");
		TextureManager::getSingleton().remove("refraction");
		TextureManager::getSingleton().remove("reflection");
	}
    // Just override the mandatory create scene method
    void createScene(void)
    {
		// Set default ambient light
		mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));

		setupFish();
		//setupFish1();
		setupContent();
		 engine = createIrrKlangDevice();
		 engineExplosion = createIrrKlangDevice();

        
        // Create the SkyBox
        mSceneMgr->setSkyBox(true, mSkyBoxes[mCurrentSkyBox], 99999*3, true);

//------------------------------------------------ Set some camera params------------------------------------------------------------------//
        mCamera->setFarClipDistance(99999*6);
		//mCamera->setPosition(312.902,206.419,1524.02);
		mCamera->setPosition(0,0,0);

		HeadNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		
		HeadNodeT = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		HeadNodeT->setPosition(-4500, 147, 5000);

HeadNode->setPosition(-4500, 147, 5000);

//HeadNode->setScale(100,100,30);
//HeadNode->attachObject(mCamera);

cameraNode=HeadNode->createChildSceneNode();
cameraNode->setPosition(0, 0, 0);
cameraNode->attachObject(mCamera);



//GunNode = HeadNode->createChildSceneNode();
/*GunNode->attachObject(mCamera);
*/
GYawNodeT = HeadNode->createChildSceneNode();
GYawNodeT->setPosition(0, 0, 0);

GYawNode = HeadNode->createChildSceneNode();
GYawNode->setPosition(0, 0, 0);


//GYawNode->pitch( Ogre::Degree(90 ) );
//GYawNode->attachObject(mCamera);

GPitchNode= GYawNode->createChildSceneNode();
GPitchNode->setPosition(0, 0, 0);

GPitchNodeT= GYawNodeT->createChildSceneNode();
GPitchNodeT->setPosition(0, 0, 0);
//GPitchNode->attachObject(mCamera);

		//mCamera->setOrientation(Ogre::Quaternion(0.998, -0.0121, -0.0608, -0.00074));

	    // Light
		Ogre::Light *mLight = mSceneMgr->createLight("Light0");
		mLight->setPosition(mSunPosition[mCurrentSkyBox]);
		mLight->setDiffuseColour(1, 1, 1);
		mLight->setSpecularColour(mSunColor[mCurrentSkyBox].x,
			                      mSunColor[mCurrentSkyBox].y,
								  mSunColor[mCurrentSkyBox].z);

		// Hydrax initialization code ---------------------------------------------
		// ------------------------------------------------------------------------

        // Create Hydrax object
		mHydrax = new Hydrax::Hydrax(mSceneMgr, mCamera, mWindow->getViewport(0));

		// Create our projected grid module  
		Hydrax::Module::ProjectedGrid *mModule 
			= new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
			                                    mHydrax,
												// Noise module
			                                    new Hydrax::Noise::Perlin(/*Generic one*/),
												// Base plane
			                                    Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
												// Normal mode
												Hydrax::MaterialManager::NM_VERTEX,
												// Projected grid options
										        Hydrax::Module::ProjectedGrid::Options(/*264 /*Generic one*/));

		// Set our module
		mHydrax->setModule(static_cast<Hydrax::Module::Module*>(mModule));

		mHydrax->loadCfg("HydraxDemo.hdx");

        // Create water
        mHydrax->create();

		
		mHydrax->getMaterialManager()->addDepthTechnique(
			static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("Island"))
			->createTechnique());

		// Create palmiers
		//createPalms(mSceneMgr);

		// Create text area to show skyboxes information
		createTextArea();

//--------------------------------------------------bullet mesh----------------------------------//		
		DVBullet= mSceneMgr->createEntity("razor", "bullet.mesh");
		Bullet = GPitchNode->createChildSceneNode();
		//Bullet->attachObject(DVBullet);
		
		Bullet->setPosition(10,140,-10);
		Bullet->setVisible(true);

		BulletTemp=GPitchNode->createChildSceneNode();
		BulletTemp->setPosition(10,140,-10);

		tempBullet=mSceneMgr->getRootSceneNode()->createChildSceneNode();
		tempBullet->attachObject(DVBullet);
		tempBullet->setPosition(0,-140,0);
		tempBullet->scale(3.6,3.6,3.6);
		//tempBullet->pitch( Ogre::Degree(90 ) );
		
		expboat1= mSceneMgr->createEntity("razor1", "cube.mesh");
		//expboat = GYawNode->createChildSceneNode();
		expboat = HeadNode->createChildSceneNode();
		expboat->attachObject(expboat1);		
		expboat->setPosition(0,0,0);
		//expboat->scale(2,2,2);
		expboat->setVisible(true);
		//mSceneMgr->showBoundingBoxes(true);


		enemycraftposition= mSceneMgr->getRootSceneNode()->createChildSceneNode();
		enemycraftposition->setPosition(joyshipPos);
		enemycraftposition->yaw(Degree(90));

		ent94 = mSceneMgr->createEntity("ship94", /*"Jetliner.mesh"*/"ship ltte no1.mesh");
		ship94 = enemycraftposition->createChildSceneNode();		
		ship94->attachObject(ent94);	
		//ship94->attachObject(ent94);
		ship94->scale(0.5,1.5,1);
		ship94->setPosition(/*ship94pos*/-2000,-180,-1280);
		ship94->yaw(Degree(0));



		
		ent95 = mSceneMgr->createEntity("ship95", /*"Jetliner.mesh"*/"ship ltte no1.mesh");
		ship95 = enemycraftposition->createChildSceneNode();		
		ship95->attachObject(ent95);	
		//ship94->attachObject(ent94);
		ship95->scale(0.5,1.5,1);
		ship95->setPosition(/*ship94pos*/-20,-180,-1280);
		ship95->yaw(Degree(0));
		
		 //
		// Add frame listener
		mRoot->addFrameListener(new ExampleHydraxDemoListener(mWindow, mCamera, mSceneMgr));        
    }
	
	// Create text area to show skyboxes information
	void createTextArea()
	{
		// Create a panel
		Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
			OverlayManager::getSingleton().createOverlayElement("Panel", "HydraxDemoInformationPanel"));
		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(10, 10);
		panel->setDimensions(400, 400);

		// Create a text area
		mTextArea = static_cast<Ogre::TextAreaOverlayElement*>(
			OverlayManager::getSingleton().createOverlayElement("TextArea", "HydraxDemoInformationTextArea"));
		mTextArea->setMetricsMode(Ogre::GMM_PIXELS);
		mTextArea->setPosition(0, 0);
		mTextArea->setDimensions(100, 100);
		mTextArea->setCharHeight(16);
		mTextArea->setCaption(" "  + Ogre::StringUtil::split(mSkyBoxes[mCurrentSkyBox],"/")[3] + " ");
		mTextArea->setFontName("BlueHighway");
		mTextArea->setColourBottom(ColourValue(0.3, 0.5, 0.3));
		mTextArea->setColourTop(ColourValue(0.5, 0.7, 0.5));



		mTextArea55 = static_cast<Ogre::TextAreaOverlayElement*>(
			OverlayManager::getSingleton().createOverlayElement("TextArea", "HydraxDemoInformationTextArea5"));
		mTextArea55->setMetricsMode(Ogre::GMM_PIXELS);

		mTextArea56 = static_cast<Ogre::TextAreaOverlayElement*>(
			OverlayManager::getSingleton().createOverlayElement("TextArea", "HydraxDemoInformationTextArea6"));
		mTextArea56->setMetricsMode(Ogre::GMM_PIXELS);



		mTextArea55->setPosition(200, 200);
		mTextArea55->setDimensions(300, 300);
		mTextArea55->setCaption("");
		mTextArea55->setCharHeight(60);
		mTextArea55->setFontName("BlueHighway");
		mTextArea55->setColourBottom(ColourValue(1, 0, 0));
		mTextArea55->setColourTop(ColourValue(1, 0, 0));


		mTextArea56->setPosition(10, 30);
		mTextArea56->setDimensions(30, 30);
		mTextArea56->setCaption("");
		mTextArea56->setCharHeight(80);
		mTextArea56->setFontName("BlueHighway");
		mTextArea56->setColourBottom(ColourValue(1, 0, 0));
		mTextArea56->setColourTop(ColourValue(1, 0, 0));

		//
		///* VSC - Mision Failed*/
		//mTextArea55->setPosition(100, 300);
		//mTextArea55->setDimensions(300, 300);
		//mTextArea55->setCaption("");
		//mTextArea55->setCharHeight(80);
		//mTextArea55->setFontName("BlueHighway");
		//mTextArea55->setColourBottom(ColourValue(1, 0, 0));
		//mTextArea55->setColourTop(ColourValue(1, 0, 0));

		// Create an overlay, and add the panel
		Ogre::Overlay* overlay = OverlayManager::getSingleton().create("OverlayName");
		overlay->add2D(panel);

		// Add the text area to the panel
		panel->addChild(mTextArea);
		panel->addChild(mTextArea55);//msn fld
		panel->addChild(mTextArea56);


		// Show the overlay
		overlay->show();
	}
};

int main(int argc, char **argv)
{
    // Create application object
    SampleApp app;
	
    try
    {
        app.go();
    }
    catch ( Ogre::Exception& e )
    {
        std::cerr << "An exception has occured: " << e.getFullDescription();
    }
	    return 0;
}
