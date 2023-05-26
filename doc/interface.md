# LoRa Mesh Network Interface Specification
This interface uses LoRa and MQTT for communication. Each node uses LoRa to send and receive packets.

## Messages
Each package contains at least:
- topic: The MQTT topic
- payload: A variable length byte/string including these fields
  - sender uuid: A uuid of the node that initially sent the message
  - timestamp: The timestamp for when the message was sent
  - message uid: unique identifier of the message (is this needed? might just use sender uuid and timestamp to check)

Using the folliowing format:
```
  "head":{
    "topic": "esp32/sample-topic",
    "uuid": "aabbccdd",
    "messageTimestamp": "2023-05-26T14:50:30+02:00",
    "messageUid": "aabbccdd/2023-05-26T14:50:30+02:00"
  }
```

## Interface

The interface uses JSON for its payload.

## Topics

All the topics are filled with sample data

### System data

Information about a specific mesh node

#### Created at
Topic:
```
esp32/system-info/created-at
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "createdAt": {
      "type": "timestamp",
      "value": "2023-05-26T14:50:30+02:00"
    }
  }
}
```

#### Updated at
Topic:
```
esp32/system-info/updated-at
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "updatedAt": {
      "type": "timestamp",
      "value": "2023-05-26T14:50:30+02:00"
    }
  }
}
```

#### Health status
Topic:
```
esp32/system-info/health-status
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "createdAt": {
      "type": "timestamp",
      "value": "2023-05-26T14:50:30+02:00"
    }
  }
}
```

#### Battery status
Topic:
```
esp32/system-info/battery-status
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "battery": {
      "type": "int",
      "value": "69"
    }
  }
}
```

#### Signal strength
Topic:
```
esp32/system-info/signal-strength
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "signalStrength": {
      "type": "float",
      "value": "500.3"
    }
  }
}
```

### System data

#### Created at
Topic:
```
esp32/system-info/created-at
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "createdAt": {
      "type": "timestamp",
      "value": "2023-05-26T14:50:30+02:00"
    }
  }
}
```

#### Updated at
Topic:
```
esp32/system-info/updated-at
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "updatedAt": {
      "type": "timestamp",
      "value": "2023-05-26T14:50:30+02:00"
    }
  }
}
```

#### Health status
Topic:
```
esp32/system-info/health-status
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "createdAt": {
      "type": "timestamp",
      "value": "2023-05-26T14:50:30+02:00"
    }
  }
}
```

#### Battery status
Topic:
```
esp32/system-info/battery-status
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "battery": {
      "type": "int",
      "value": "69"
    }
  }
}
```

#### Signal strength
Topic:
```
esp32/system-info/signal-strength
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "signalStrength": {
      "type": "float",
      "value": "500.3"
    }
  }
}
```

### Sensor Data

Still unsure if approach is good. Might be better to research and check if generic sensor data payload would be valid.

Topic für alle Sensoren:
```
esp32/sensor/#
```

#### Camera

Topic:
```
esp32/sensor/camera
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
      "sensor": {
        "uuid": "cam/MAC",
        "data": "200"
      }
  }
}
```

### Generic Message Acknowledge
Topic:
```
esp32/acknowledge
```
Payload:
```
{
  ...(minimum info and then content following)
  "content": {
    "messageUid": "aabbccdd/2023-05-26T14:50:30+02:00"
  }
}
```

Acknowledges are published back to the gateway as soon as a message is received by the node.