#include "Scene.h"
#include "Actor.h"

#include "Core/StringHelper.h"
#include "Renderer/Renderer.h"


namespace viper {
	void Scene::Update(float dt) {
		//update all actors
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}

		//remove destroyed actors
		for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if ((*iter)->destroyed) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	//check for collisions
	for (auto& actorA : m_actors) {
		for (auto& actorB : m_actors) {
			if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

			float distance = (actorA->transform.position - actorB->transform.position).Length();
			if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
				actorA->OnCollision(actorB.get());
				actorB->OnCollision(actorA.get());
			}
		}
	}


	}


	void Scene::Draw(class Renderer& renderer) {
		for (auto& actor : m_actors) {
			actor->Draw(renderer);

		}
	}

	void Scene::AddActor(std::unique_ptr<class Actor> actor) {
		actor->scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors() {
		m_actors.clear();
	}
	


		
}