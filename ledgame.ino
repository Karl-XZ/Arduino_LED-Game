// 定义LED和按钮引脚
int led[] = {2, 3, 4, 5}; // led引脚,可以自己换
int anniu[] = {6, 7, 8, 9}; // 按钮引脚，同上
int suiji[10]; // 随机数组
int player[10]; // 存储玩家的选择
int fen = 0; // 分数
// int numbers[4] = {0, 1, 2, 3};// 一个1到4的数组，用来搞随机数

void setup() {
  // 初始化led
  for (int i = 0; i < 4; i++) {// 注意i的值是0123不是1234！下同
    pinMode(led[i], OUTPUT);
  }
  
  // 初始化按钮
  for (int i = 0; i < 4; i++) {
    pinMode(anniu[i], INPUT_PULLUP);
  }

  int numbers[4] = {0, 1, 2, 3};// 一个1到4的数组，用来搞随机数
  // 初始化随机数
  randomSeed(analogRead(0));// 随机数生成器
  for (int i = 0; i < 4; i++) {
    int n;// 随机数个体变量
    bool YN;// 判断变量
    do {
        n = random(4); // 生成一个0到3之间的随机数
        YN = false; // 初始化YN为false
        for (int x = 0; x < i; x++) {
            if (suiji[x] == n) {
                YN = true; // 如果重复，则将YN设置为true
                break; // 跳出内层循环
            }
        }
    } while (YN); // 如果当前随机数重复，则重新生成

    suiji[i] = n; // 储存随机数
  }
}


void loop() {
  
  for (int round = 0; round < 10; round++) {// 10轮
    for (int i = 0; i <= round; i++) {// 游戏主体
      while (digitalRead(anniu[0]) || digitalRead(anniu[1]) || digitalRead(anniu[2]) || digitalRead(anniu[3]));// 有按钮被按下后开始游戏
      
      if (digitalRead(anniu[suiji[i]]) == LOW) {// 猜对了
        player[i] = suiji[i];
        digitalWrite(led[player[i]], HIGH);
        delay(300);
        digitalWrite(led[player[i]], LOW);
      } else {// 猜错了
        player[i] = -1;
        digitalWrite(led[0], HIGH);
        digitalWrite(led[1], HIGH);
        digitalWrite(led[2], HIGH);
        digitalWrite(led[3], HIGH);
        delay(500);
        digitalWrite(led[0], LOW);
        digitalWrite(led[1], LOW);
        digitalWrite(led[2], LOW);
        digitalWrite(led[3], LOW);
        delay(500);
        digitalWrite(led[0], HIGH);
        digitalWrite(led[1], HIGH);
        digitalWrite(led[2], HIGH);
        digitalWrite(led[3], HIGH);
        delay(500);
        digitalWrite(led[0], LOW);
        digitalWrite(led[1], LOW);
        digitalWrite(led[2], LOW);
        digitalWrite(led[3], LOW);
        delay(500);
      }
    }
    
    bool correct = true; // 判断正确与否
    for (int i = 0; i <= round; i++) {
      if (player[i] != suiji[i]) {
        correct = false;
        break;
      }
    }

    // 更新分数
    if (correct) {
      fen++;
    }

    Serial.print("Round ");// 显示分数
    Serial.print(round + 1);
    Serial.print(": fen = ");
    Serial.println(fen);

    if (fen >= 4) {// 游戏胜利
      Serial.println("YOU WIN!");
      while (true);
    }
  }
  
  Serial.println("WASTED");// 游戏失败
  while (true);
}
