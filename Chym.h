class Chym {

private:
  int frameCount;
  int x; 
  int y;
  int deltaIde;
  int delayFrame;

  int jumpCount; 
  int maxJumpCount;
  int moveSpeed;

  bool _isDead;
public: 
  void respawn() {
    x = 24; 
    y = 20;
    deltaIde = -1;
    moveSpeed = 1;
    jumpCount = 0;
    _isDead = false;
  }
  
  Chym() {
    frameCount = 0;
    delayFrame = 0;
    maxJumpCount = 20;
    respawn();
  }
  
  void render() {
    if (frameCount < ANIM_FRAME / 2) {
      display.drawBitmap(x, y, flappybird_frame_1, 16, 12, 1);		
    } 
    else {
      display.drawBitmap(x, y, flappybird_frame_2, 16, 12, 1);			
    }
  }

  void update() {
    delayFrame++;
    if (delayFrame == DELAY_FRAME) {
      y += deltaIde * moveSpeed;
      delayFrame = 0;
    }

    if (y > 35) {
      _isDead = true;
    }

    frameCount++;
    if (frameCount >= ANIM_FRAME) frameCount = 0;
  }

  bool isDead() {
    return _isDead;
  }
  
  void die() {
    _isDead = true;
  }

  void cancelJump() {
    jumpCount = 0;
    flyDown();
  }

  void flyUp() {
    if (jumpCount < maxJumpCount) {
      deltaIde = -1; 
      moveSpeed = 3;	
      jumpCount++;
    } 
    else {
      flyDown();
    }
  }

  void flyDown() {
    deltaIde = 1; 
    moveSpeed = 1;
  }
  
  int getX() {
    return x;
  }
  
  int getY() {
    return y;
  }

};

