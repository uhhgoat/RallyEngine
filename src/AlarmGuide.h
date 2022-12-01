/*! \page alarmdemo Adding Timers

\section almsetup Alarms
Timers, or Alarms, are a component of GameObject. To give an object Access to alarms, simply derive from GameObject. \n
A given object may have up to 3 different alarms associated with it at a time. \n
To utilize these alarms, make sure to declare the Alarm methods in your game object. \n
\code
class Player : public GameObject, public Align16
{
public:
	<...>
	virtual void Alarm0();
	virtual void Alarm1();
	virtual void Alarm2();
};
\endcode
\n
Next, make sure to define what you would like each Alarm to do.
\n
\code
void Player::Alarm0()
{
	DebugMsg::out("ZERO!\n");
}
void Player::Alarm1()
{
	DebugMsg::out("ONE!\n");
}
void Player::Alarm2()
{
	DebugMsg::out("TWO!\n");
}
\endcode
\n
\section almreg Registration/Deregistration
In order to have the engine call these alarms, they need to be registered. \n
Each alarm must be registered with a time parameter, in seconds, for how long to wait before triggering the alarm.
\n
\code
	Alarmable::SubmitAlarmRegistration(1, AlarmableManager::ALARM_0);
	Alarmable::SubmitAlarmRegistration(2, AlarmableManager::ALARM_1);
	Alarmable::SubmitAlarmRegistration(3, AlarmableManager::ALARM_2);
\endcode
\n
Alarms will automatically Deregister once triggered, so there is no need to worry about cleanup in the alarms. \n
However, if you wish to cancel an alarm previously registered, you must Deregister it manually.
\n
\code
	Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
\endcode
\n
With these tools, repeating timers can also be made with ease by simply registering a new alarm or the same alarm
in the callback of an alarm. \n
The following example will call Alarm0 to print "ZERO!" once every second.
\n
\code
void Player::Alarm0()
{
	DebugMsg::out("ZERO!\n");
	Alarmable::SubmitAlarmRegistration(1, AlarmableManager::ALARM_0);
}
\endcode
\n
\n
\n

*/