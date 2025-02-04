# Pawn

- Pawn을 이용한 움직임 구현
- const float DeltaTime = GetWorld()->GetDeltaSeconds()을 통해 프레임 수에 따른 차이를 보간
- MoveDir = MoveDir.GetSafeNormal()을 통해 인풋 벡터의 크기를 1로 제한하여, 방향에 따라 속도 차이를 보간
- SpringArm->SetRelativeRotation(FRotator(LookDirection.Y + SpringArm->GetDesiredRotation().Pitch,0, 0));
- SetActorRotation(FRotator(0, LookDirection.X + GetActorRotation().Yaw, 0));
- 좌우 회전의 경우 오브젝트의 전체 회전
- 상하 회전의 경우 스프링암을 회전시켜 차등을 줌
