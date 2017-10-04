#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <message_ui/sent_msg.h>
#include "counter_node/counter.h"
//#include "counter_node/counterRequest.h"
//#include "counter_node/counterResponse.h"
#include <arithmetic_node/arithmetic_reply.h>

int num_reply_msg = 0;
int num_sent_msg = 0;

ros::Time last_sent_msg_time;
ros::Time last_reply_msg_time;

ros::Subscriber reply_msg_sub;
ros::Subscriber arithmetic_reply_msg_sub;
ros::Subscriber sent_msg_sub;

//ros::Time begin = ros::Time::now();

void sent_msg_callback(const message_ui::sent_msg msg)
{
	num_sent_msg++;
	last_sent_msg_time = msg.header.stamp;
}

void reply_msg_callback(const chatbot_node::reply_msg msg)
{
	num_reply_msg++;
	//last_reply_msg_time = msg.header.stamp;
    last_reply_msg_time = ros::Time::now();
}

void arithmetic_reply_msg_callback(const arithmetic_node::arithmetic_reply msg)
{
	num_reply_msg++;
	//last_reply_msg_time = msg.header.stamp;
    last_reply_msg_time = ros::Time::now();
 }


bool doyothing(counter_node::counter::Request &req,
               counter_node::counter::Response &res)
{
    if(req.req_id == 0)
    {
        //here we want total number of messages so all reply and send

        res.reply=num_reply_msg+num_sent_msg;

        return true;
    }

    else if (req.req_id ==1)
    {

        res.reply=num_reply_msg;
        return true;
    }

    else if (req.req_id ==2){

        res.reply=num_sent_msg;
        return true;
    }

    else if (req.req_id ==3){

        //Time elapsed since last reply message
        double now = ros::Time::now().toSec();

        res.reply=now-last_reply_msg_time.toSec();
        return true;


    }

    else if (req.req_id ==4){

        double now = ros::Time::now().toSec();

        res.reply=now-last_sent_msg_time.toSec();
        return true;

    }

}

int main(int argc, char **argv) {

  ros::init(argc, argv, "counter_node");
  ros::NodeHandle n;

  reply_msg_sub = n.subscribe("reply_msg", 1000, reply_msg_callback);
  sent_msg_sub = n.subscribe("sent_msg", 1000, sent_msg_callback);

  arithmetic_reply_msg_sub = n.subscribe("arithmetic_reply", 1000, arithmetic_reply_msg_callback);

    // if request id is 0 then

  //request will be sent from message.ui node



    ros::ServiceServer service = n.advertiseService("message_counter",doyothing);




  ros::Rate loop_rate(20);

  while(ros::ok()) {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
