import { CommonModule } from '@angular/common';
import { Component, OnInit } from '@angular/core';
import { RouterOutlet } from '@angular/router';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, CommonModule],
  templateUrl: './app.component.html',
  styleUrl: './app.component.scss'
})
export class AppComponent  implements OnInit {
  
  public title = 'numbers';

  public numbers: number[] = [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5];

  public selectedLength: number = 0;

  public lengthOptions: { text: string; value: number }[] = [];
  
  constructor() {}

  public ngOnInit(): void {
    this.setLengthOptions();
  }

  public setLengthOptions(): void {
    for (let i = 1; i <= 100; i++) {
      this.lengthOptions.push({ text: i.toString(), value: i });
    }
  }
  
}
