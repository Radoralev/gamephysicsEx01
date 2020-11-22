#include "MassSpringSystemSimulator.h"

MassSpringSystemSimulator::MassSpringSystemSimulator() {
	m_fMass = 10;
	m_fStiffness = 40;
	m_fDamping = 0;
	m_iIntegrator = 0;

	massPoints;
	springs;

	m_externalForce = Vec3();
	m_mouse.x = 0;
	m_mouse.y = 0;
	m_trackmouse.x = 0;
	m_trackmouse.y = 0;


}

void MassSpringSystemSimulator::setMass(float mass) {
	this->m_fMass = mass;

}

void MassSpringSystemSimulator::setStiffness(float stiffness) {
	this->m_fStiffness = stiffness;
}

void MassSpringSystemSimulator::setDampingFactor(float damping) {
	this->m_fDamping = damping;
}

int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed) {

	mass_point mp = { position, Velocity, isFixed };

	this->massPoints.push_back(mp);


	return this->massPoints.size() - 1;
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength) {

	spring s = { masspoint1,  masspoint2,  initialLength };
	this->springs.push_back(s);
}


int MassSpringSystemSimulator::getNumberOfMassPoints() {

	return this->massPoints.size();

}

int MassSpringSystemSimulator::getNumberOfSprings() {

	return this->springs.size();
}

Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index) {

	return this->massPoints.at(index).position;
}

Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index) {

	return this->massPoints.at(index).Velocity;
}

void MassSpringSystemSimulator::applyExternalForce(Vec3 force) {

	this->m_externalForce = force;
}

const char* MassSpringSystemSimulator::getTestCasesStr() {

	return "MassSpringSystem";

}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass* DUC) {

	this->DUC = DUC;
	TwAddVarRW(DUC->g_pTweakBar, "Integrator", TW_TYPE_INT32, &m_iIntegrator, "min=0 max=2");

}

void MassSpringSystemSimulator::reset() {

	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;

}

void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext) {

	int p1 = this->addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
	int p2 = this->addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
	//this->addSpring(p1, p2, 1);
	DUC->setUpLighting(Vec3(), 0.4 * Vec3(1, 1, 1), 100, 0.6 * Vec3(0.97, 0.86, 1));
	DUC->drawSphere(this->getPositionOfMassPoint(p1), 0.05);
	DUC->drawSphere(this->getPositionOfMassPoint(p2), 0.05);
	DUC->beginLine();
	//DUC->drawLine(Vec3(0, 0, 0), Vec3(255, 0, 0),Vec3(0, 2, 0), Vec3(255, 0, 0));
	DUC->drawLine(this->getPositionOfMassPoint(p1), Vec3(255, 0, 0), this->getPositionOfMassPoint(p2), Vec3(255, 0, 0));
	DUC->endLine();
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase) {}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed) {}

void MassSpringSystemSimulator::simulateTimestep(float timeStep) {

	switch (this->m_iIntegrator) {
	case 0: euler(timeStep); break;
	case 1:break;
	case 2: midpoint(timeStep); break;

	}

}

void MassSpringSystemSimulator::onClick(int x, int y) {

	m_trackmouse.x = x;
	m_trackmouse.y = y;

}

void MassSpringSystemSimulator::onMouse(int x, int y) {

	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;

}

void MassSpringSystemSimulator::euler(float timestep) {


}

void MassSpringSystemSimulator::midpoint(float timestep) {


}

Vec3 MassSpringSystemSimulator::computeElasticForces(MassSpringSystemSimulator::spring& spring) {

}

void integratePosition(struct mass_point& mass_point) {}
void integrateVelocity(struct mass_point& mass_point) {}