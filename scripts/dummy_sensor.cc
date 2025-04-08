#include <gz/sim/System.hh>
#include <gz/sim/Util.hh>
#include <gz/plugin/Register.hh>
#include <gz/transport/Node.hh>
#include <gz/msgs/stringmsg.pb.h>

using namespace gz;
using namespace gz::sim;

class DummySensor : public System,
public ISystemConfigure,
public ISystemPostUpdate
{
public:
void Configure(const Entity &entity,
const std::shared_ptr<const sdf::Element> & /*sdf*/,
EntityComponentManager & /*ecm*/,
EventManager & /*eventMgr*/) override
{
this->entity = entity;
gzmsg << "[DummySensor] Plugin configured.\n";

this->publisher = this->node.Advertise<gz::msgs::StringMsg>("/dummy_sensor_topic");
if (!this->publisher)
{
gzerr << "[DummySensor] Failed to create publisher.\n";
}
this->published = false;
}

void PostUpdate(const UpdateInfo &, const EntityComponentManager &) override
{

gz::msgs::StringMsg msg;
msg.set_data("Hello World from DummySensor");
this->publisher.Publish(msg);
gzmsg << "[DummySensor] Published message.\n";
this->published = true;

}

private:
Entity entity;
transport::Node node;
transport::Node::Publisher publisher;
bool published;
};

GZ_ADD_PLUGIN(DummySensor,
System,
ISystemConfigure,
ISystemPostUpdate)